#include <iostream>

//宏前面加上##的作用在于：当可变参数的个数为0时，这里的## 起到把前面多余的","去掉的作用
#define DEBUG_INFO(format, ...) printf("File:%s, Line:%d, Function:%s, %s", \
	__FILE__, __LINE__ , __FUNCTION__, ##__VA_ARGS__);

int main(){
    DEBUG_INFO("%s", "\n");
}