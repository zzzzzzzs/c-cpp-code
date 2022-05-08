#include "print.h"

typedef struct _list {
  unsigned char inited;
} List;

int main() {
  List aa;
  aa.inited = 10;
  print(aa);
  print(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  print("a");
  print(3, " / ", 2, " = ", 1.5);
  print("A", 10, -10);
  print('A');
  print("sadad");
  // DBG_PRINTF("%d", 1);
    // 带颜色printf
  printf("\033[0;32m");
  printf("Hello World!\n");
  printf("\033[0m");
  if (0) {
    DBG_PRINTF("asdads");
  }else{
    DBG_PRINTF("asdadsasdsadads");
  }
}