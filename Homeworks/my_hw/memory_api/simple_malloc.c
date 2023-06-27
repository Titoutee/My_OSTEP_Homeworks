#include "stdlib.h"
#include "stdio.h"

int main(void) {
    int *data = malloc(sizeof(int) * 100);
    data[100] = 0;
    printf("%d", data[100]);
    free(data);
    return 0;
}