#include <iostream>

void modifyValue(int* ptr) {
    *ptr = 10; // 解引用指针并修改其值
}

void modifyReference(int& ref) {
    ref = 20; // 修改引用所绑定的值
}

int main() {
    int value = 5;
    
    modifyValue(&value); // 传递变量的地址
    std::cout << "Modified value: " << value << std::endl; // 输出：Modified value: 10

    modifyReference(value); // 传递变量作为引用
    std::cout << "Modified value: " << value << std::endl; // 输出：Modified value: 20

    return 0;
}
