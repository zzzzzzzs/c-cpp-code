#include<Windows.h>
#include <iostream>
// 获取当前窗口的信息名
int main(){
    Sleep(2000);
    std::cout << "Hello World!\n";
    char title[255];
    GetWindowText(GetForegroundWindow(), title, sizeof(title));
    std::cout << title << std::endl;
}
