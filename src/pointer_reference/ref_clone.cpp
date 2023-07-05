#include <iostream>
#include <string>


class Person {
private:
    std::string name;

public:
    // 构造函数
    Person(const std::string& n) : name(n) {}

    // 第一个 get() 函数：返回对 name 的引用
    const std::string& getNameRef() const {
        std::cout << "ref name addr: " << &name << std::endl;
        return name;
    }

    // 第二个 get() 函数：返回 name 的拷贝
    const std::string getNameCopy() const {
        std::cout << "copy name addr: " << &name << std::endl;
        return name;
    }
};

int main() {
    Person person("Alice");

    // 使用第一个 get() 函数返回对 name 的引用
    const std::string& ref = person.getNameRef();
    std::cout << "Reference Value: " << ref << ", Address: " << &ref << " [REFERENCE]" << std::endl;

    // 使用第二个 get() 函数返回 name 的拷贝, 这里和原来的地址不一样了，进行了拷贝
    const std::string copy = person.getNameCopy(); 
    std::cout << "Copy Value: " << copy << ", Address: " << &copy << " [COPY]" << std::endl;

    return 0;
}
