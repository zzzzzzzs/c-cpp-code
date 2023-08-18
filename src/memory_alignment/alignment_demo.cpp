#include <stdio.h>

// TODO 内存对齐
struct __attribute__((aligned(16))) Data {
    int a;
    double b;
};

int main() {
    printf("Size of struct Data: %zu\n", sizeof(struct Data));
    return 0;
}