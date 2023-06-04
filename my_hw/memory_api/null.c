#include "stdlib.h"
#include "stdio.h"

int main(void) {
    int *p = (int*) malloc(sizeof(int) * 1);
    p = NULL;
    printf("Result: %d", *p);
    free(p);
    return 0;
}