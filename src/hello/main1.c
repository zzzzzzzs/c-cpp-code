#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

// %d--> 为int

// %u--> 为unsigned int

// %ld--> 为long int或long

// %lu--> for unsigned long intor long unsigned intorunsigned long

// %lld--> 为long long int或long long

// %llu--> 为unsigned long long int或unsigned long long

int main1(int argc, char** argv) {
  long long num = 0;
  // 循环
  // 当前时间
  clock_t start_t;
  start_t = clock();

  // for (int i = 0; i < 100000000000; i++) {
  //   for (int j = 0; j < 100000000000; j++) {
  //     for (int k = 0; k < 100000000000; k++) {
  //       num++;
  //     }
  //   }
  // }
  for (long long i = 0; i < 10000000000000000; i++) {
    num++;
  }
  // 结束时间
  clock_t finish_t;
  finish_t = clock();
  printf("%lld\n", num);
  printf("%f\n", (double)(finish_t - start_t) / CLOCKS_PER_SEC);
  // 带颜色printf
  printf("\033[0;32m");
  printf("Hello World!\n");
  printf("\033[0m");
    printf("\033[0;32mhello world!\n\033[0m");
    // 打印红色
    printf("\033[0;31m");
    printf("Hello World!\n");
    printf("\033[0m");
    
  return 0;
}
