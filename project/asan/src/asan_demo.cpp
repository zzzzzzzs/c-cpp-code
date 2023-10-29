#include <memory>
#include <iostream>

class Node {
public:
    std::shared_ptr<Node> next;

    Node() {
        std::cout << "Node created" << std::endl;
    }

    ~Node() {
        std::cout << "Node destroyed" << std::endl;
    }
};

int main() {
    std::shared_ptr<Node> node1 = std::make_shared<Node>();
    std::shared_ptr<Node> node2 = std::make_shared<Node>();

    // 创建循环引用
    node1->next = node2;
    node2->next = node1;

    return 0;
}
