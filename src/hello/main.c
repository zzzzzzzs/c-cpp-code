#include <stdio.h>
#include <time.h>
#include <windows.h>
int main(int argc, char** argv) {
  int num = 0;
  // 循环
  // 当前时间
  time_t now;
  time(&now);

  //   for (int i = 0; i < 100000000000; i++) {
  //     for (int j = 0; j < 100000000000; j++) {
  //       for (int k = 0; k < 100000000000; k++) {
  //         num++;
  //       }
  //     }
  //   }
  for (int i = 0; i < 100000000000; i++) {
    num++;
    printf("%d\n", num);
  }
  // 结束时间
  time_t end;
  time(&end);
  printf("%d\n", num);
  printf("%d\n", end - now);

  //   printf("hello world!\n");
  //   return 0;
}
