#include "stdlib.h"
#include "stdio.h"

typedef struct {
    char *arr;
    size_t data_size;
    size_t capacity;
} Vec;

int init_vec(Vec *vec);
void vec_push(Vec *vec, char elt);
void vec_pop(Vec *vec);
char *inner(Vec *vec);