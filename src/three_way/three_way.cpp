#include <iostream>


// TODO 三路比较运算符 c++20 支持的，目前还没有搞定

class decimal12_t {
public:
    decimal12_t(int value) : number(value) {}

    // Example cmp() function for illustration purposes
    // int cmp(const decimal12_t& other) const {
    //     if (number < other.number) return -1;
    //     if (number > other.number) return 1;
    //     return 0;
    // }

    // // Three-way comparison operator
    // auto operator<=>(const decimal12_t& value) const {
    //     return cmp(value) <=> 0;
    // }

private:
    int number;
};

int main() {
    // decimal12_t num1(12345678);
    // decimal12_t num2(98765432);
    // decimal12_t num3(12345678);

    // // Using the operator<=>
    // if (num1 < num2) {
    //     std::cout << "num1 is less than num2" << std::endl;
    // } else if (num1 > num2) {
    //     std::cout << "num1 is greater than num2" << std::endl;
    // } else {
    //     std::cout << "num1 is equal to num2" << std::endl;
    // }

    // if (num1 == num3) {
    //     std::cout << "num1 is equal to num3" << std::endl;
    // } else {
    //     std::cout << "num1 is not equal to num3" << std::endl;
    // }

    return 0;
}
