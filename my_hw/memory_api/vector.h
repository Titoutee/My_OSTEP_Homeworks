#include "stdlib.h"
#include "stdio.h"

typedef struct {
    int *arr;
    size_t data_size;
    size_t capacity;
} Vec;

int init_vec(Vec *vec);
void push(Vec *vec, int elt);
void pop(Vec *vec);
void vec_free(Vec *vec);