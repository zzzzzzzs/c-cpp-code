#include <iostream>
#include <vector>

class BitMap {
private:
    std::vector<unsigned char> map; // 使用字节数组作为位图的基础结构
    size_t size; // 位图中位的总数

public:
    // 构造函数，初始化位图的大小
    BitMap(size_t numBits) : size(numBits), map((numBits + 7) / 8, 0) {}

    // 设置位（将位设置为1）
    void set(size_t index) {
        if (index >= size) {
            std::cerr << "Index out of bounds" << std::endl;
            return;
        }
        // 
        map[index / 8] |= 1 << (index % 8);
        // map[index >> 3] |= 1 << (index & 7);
    }

    // 清除位（将位设置为0）
    void clear(size_t index) {
        if (index >= size) {
            std::cerr << "Index out of bounds" << std::endl;
            return;
        }
        map[index / 8] &= ~(1 << (index % 8));
    }

    // 检查位是否设置（是否为1）
    bool isSet(size_t index) const {
        if (index >= size) {
            std::cerr << "Index out of bounds" << std::endl;
            return false;
        }
        // return (map[index / 8] & (1 << (index % 8))) != 0;
        return (map[index >> 3] & (1 << (index & 7))) != 0;
    }

    // 打印位图的内容
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            if (isSet(i))
                std::cout << "1";
            else
                std::cout << "0";
        }
        std::cout << std::endl;
    }
};

int main() {
    BitMap bitmap(16); // 创建一个可以存储16位的位图

    bitmap.set(1);
    // bitmap.set(7);
    // bitmap.set(10);

    bitmap.print(); // 应该打印出 0001000100010000

    // bitmap.clear(7);
    // bitmap.print(); // 现在应该打印出 0001000000010000
    return 0;
}
