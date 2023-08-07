#include <stdio.h>

struct __attribute__((aligned(16))) Data {
    int a;
    double b;
};

int main() {
    printf("Size of struct Data: %zu\n", sizeof(struct Data));
    return 0;
}