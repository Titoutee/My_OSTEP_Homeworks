#include "stdlib.h"
#include "stdio.h"

int main(void) {
    int *data = malloc(100);
    printf("%d", data[2]);
    free(&data[2]);
    return 0;
}