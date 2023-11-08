#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class SharedData {
public:
    SharedData() {}

    void produce(int value) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 模拟生产数据的过程
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _data.push(value);  // 将数据放入队列
            std::cout << "Produced: " << value << std::endl;
        }
        _cv.notify_one();  // 通知等待的消费者线程
    }

    void consume(const std::string& threadName) {
        while (true) {
            std::unique_lock<std::mutex> lock(_mutex);
            /*
            用于在等待条件变为真时挂起线程。
            在给定的互斥锁上调用 wait 时，线程将被阻塞，
            直到其他某个线程在相同的条件变量上调用了 notify_one 或 notify_all，
            并且条件谓词返回 true。
            */
            /*
            _cv.wait 函数会在等待期间将线程置于阻塞状态，这会使得线程不会一直占用 CPU。
            当线程等待条件变为真时，它会释放互斥锁，并处于非活动状态，直到被其他线程唤醒。
            */
            _cv.wait(lock, [this] { return !_data.empty(); }); 

            /*
            如果有多个线程在消费数据，使用 while (!_data.empty()) 的主要优势在于能够处理多个连续的数据。考虑以下情况：
            假设有两个消费者线程 A 和 B。如果使用 if (!_data.empty())，当一个线程被唤醒时，可能会处理一个数据并释放锁，然后另一个线程可能获得锁并发现队列中还有数据，然后处理另一个数据。这种情况下，两个线程可以交替地处理队列中的数据。
            使用 while (!_data.empty()) 可以确保线程在被唤醒后不停地处理队列中的数据，直到队列为空。这对于多个消费者的情况可能更加有效，因为每个线程都能够尽可能地处理队列中的数据。
            然而，具体的实现可能需要根据具体的需求和线程安全的考虑来调整。确保在处理数据时，对共享资源（比如队列）的访问是线程安全的是非常重要的。

            ----------------------
            如果使用 if (!_data.empty())，在多个线程并发消费数据的情况下，可能会出现一些问题，其中之一是竞态条件（Race Condition）的可能性。

            考虑以下情况：
            线程A检查队列非空，发现非空，准备处理数据。
            在线程A还没有来得及处理数据之前，线程B也检查队列非空，同样发现非空。
            线程B开始处理数据，同时线程A也在处理数据，导致数据竞争。
            这就是竞态条件的典型案例，多个线程在没有足够同步的情况下同时访问共享资源，可能导致未定义的行为。

            使用 while (!_data.empty()) 的方式可以在一个线程处理完一个数据后继续检查队列是否为空，并继续处理。这样可以确保一个线程在处理数据时不被其他线程中断，避免了竞态条件的出现。

            综上所述，使用 while (!_data.empty()) 更有助于确保在多线程环境中数据的安全处理。
            */
            while (!_data.empty()) {
                int value = _data.front();
                _data.pop();
                lock.unlock();
                // 在这里进行实际的数据处理
                // std::cout << "Thread " << std::this_thread::get_id() << " Consumed: " << value << std::endl;
                std::cout << threadName << " Consumed: " << value << std::endl;
                lock.lock();  // 重新获取锁，准备处理下一个数据
            }
        }
    }

private:
    std::mutex _mutex;
    std::condition_variable _cv;
    std::queue<int> _data;
};

int main() {
    SharedData shared_data;

    std::thread producer_thread([&shared_data]() {
        for (int i = 0; i < 5; ++i) {
            shared_data.produce(i);
        }
    });

    std::thread consumer_thread([&shared_data]() {
        shared_data.consume("Consumer 1");
    });

    std::thread consumer_thread2([&shared_data]() {
        shared_data.consume("Consumer 2");
    });

    producer_thread.join();
    consumer_thread.join();
    consumer_thread2.join();

    return 0;
}
