#include "stdlib.h"
#include "stdio.h"

int main(void) {
    int *p = (int *) malloc(sizeof(int) * 1);
    printf("%d\n", *p);
    return 0;
}