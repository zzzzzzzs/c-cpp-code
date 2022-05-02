#include "print.h"

typedef struct _list {
  unsigned char inited;
} list;

int main() {
  list aa;
  aa.inited = 10;
  print(aa);
  print(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  print("a");
  print(3, " / ", 2, " = ", 1.5);
  print("A", 10, -10);
  print('A');
  print("sadad");
}