#include "factory_creator.h"
#include <iostream>

class MyClass {
private:
    ENABLE_FACTORY_CREATOR(MyClass)

    // 私有构造函数，禁止直接创建对象
    MyClass() {}

public:
    void DoSomething() {
        // 执行某些操作
        std::cout << "Hello" << std::endl;
    }
};

int main(){
    // 通过 create_shared 创建对象
    std::shared_ptr<MyClass> obj1 = MyClass::create_shared();
    obj1->DoSomething();

    // 通过 create_unique 创建对象
    std::unique_ptr<MyClass> obj2 = MyClass::create_unique();
    obj2->DoSomething();
    
    // MyClass* obj3 = new MyClass();  // 错误！无法直接调用 new 运算符创建对象

}