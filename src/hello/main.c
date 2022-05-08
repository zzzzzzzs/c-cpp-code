#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigHandle(int sig) {
    switch(sig) {
    case SIGINT:
        printf("sigHandle: %d, SIGINT\n", sig);
        break;
    default:
        printf("sigHandle: %d, OTHER\n", sig);
        break;
    }
    // exit(1);
}

int main() {
    // signal(SIGINT, sigHandle);
    signal(SIGINT, SIG_IGN);
    
    for(;;) {
      printf("Hello World!\n");
    }
    return 0;
}