/**
 * @file
 * @brief File used to test the malloc_dbg, calloc_dbg and free_dbg functions.
 * @details
 * This file only have a main function that calls malloc, calloc and free.
 * When the program exits, memory leaks must be printed.
 * @author [tinouduart33](https://github.com/tinouduart33)
 * @see malloc_dbg.c, malloc_dbg.h
 */
// TODO if don't use the MALLOC DUB, we must comment out the #include line
#include "malloc_dbg.h"  /// For the macros malloc, calloc and free and the malloc_dbg, calloc_dbg and free_dbg functions.

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>  /// For IO operations if needed.
#include <stdlib.h>  /// For the EXIT_SUCCESS macro and the "real" malloc, calloc and free functions.
#include <sys/wait.h>

bool appStopped = true;

void sigintHandler(int sig) {
  if (sig == SIGINT) {
    // ctrl+c退出时执行的代码
    printf("ctrl+c pressed!\n");
    // 打印内存泄漏信息
    printLeaks();
    appStopped = false;
  }
}

/**
 * @brief Main function
 * @param argc number of arguments (not used)
 * @param argv list of arguments (not used)
 * @returns 0 on exit
 */
int main(int argc, char* argv[]) {
  // signal() does not handle SIGINT correctly in windows. You need to use
  // SetConsoleCtrlHandler for this purpose.
  signal(SIGINT, sigintHandler);

  int i = 0;

  printf("Hello");
  int* iptr = (int*)malloc(10 * sizeof(int));
  char* cptr = (char*)calloc(256, sizeof(char));

  free(iptr);
  free(cptr);
  while (appStopped) {
    i++;
    /* code */
    usleep(100);
    printf("%d\r\n", i);
  }
  return 0;
}
