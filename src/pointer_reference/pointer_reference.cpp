#include <iostream>

// ptr 是指针，修改变量需要解引用
void modifyValue(int* ptr) {
    *ptr = 10; // 解引用指针并修改其值
}

// 当我们将变量作为引用传递给函数时，我们实际上是在告诉函数：“使用这个变量，但不要创建它的副本，直接对原始变量进行操作。”
void modifyReference(int& ref) {
    ref = 20; // 修改引用所绑定的值
}

int main() {
    int value = 5;
    
    modifyValue(&value); // 传递变量的地址
    std::cout << "Modified value: " << value << std::endl; // 输出：Modified value: 10

    modifyReference(value); // 传递变量作为引用
    std::cout << "Modified value: " << value << std::endl; // 输出：Modified value: 20


    int* ptr = &value;

    std::cout << "Before modification: " << *ptr << std::endl;

    modifyValue(ptr);
    std::cout << "After modifyValue: " << *ptr << std::endl;

    modifyReference(*ptr); // *ptr 指的是具体的值，而不是一个地址
    std::cout << "After modifyReference: " << *ptr << std::endl;

    return 0;
}
