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

typedef struct {
  const char* ptr;
  size_t info;
} str;

#define str_null str { 0, 0 }

// test print
void test1(void) {
  str a;
  printf("%d", str_null.info);
}
int main(int argc, char** argv) {
  test1();
  return 0;
}
