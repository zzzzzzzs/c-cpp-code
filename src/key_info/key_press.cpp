#include <windows.h>
#include <iostream>

using namespace std;

BYTE state[256];

int main() {
    //----------循环检测----------
    while (true) {                                //循环检测
        if (GetKeyState(VK_LSHIFT) & 0x8000) {
            cout << "aa" << endl;
        }
        Sleep(10);                            //延时
    }
    return 0;
}
