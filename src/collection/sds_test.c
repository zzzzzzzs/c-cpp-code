#include "sds.h"
#include "../tools/print.h"
int main(){
    sds s = sdsnew("Hello, world!");
    printf("%s\n", s);
    print(s);
    sdsfree(s);
    return 0;
}