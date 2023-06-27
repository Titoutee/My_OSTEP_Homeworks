#include "vector.h"
#include "stdio.h"
#include "stdlib.h"

#define INIT_CAPA 1

void push(Vec *vec, int elt) {
  if (vec->data_size==vec->capacity) { // We have consumed all the space beforehand allocated mem
    vec->capacity *= 2; // Efficiency wants that we double the capacity
    vec->arr = (int *) realloc(vec->arr, vec->capacity * sizeof(int)); // We realloc the vector with new capacity
  }
  vec->arr[vec->data_size++] = elt; // We add the given elt and increment data_size
}

void pop(Vec *vec) {
  int popped = vec->arr[vec->data_size--];
  if (vec->data_size <= vec->capacity/4) {
    vec->capacity /= 2;
    vec->arr = realloc(vec->arr, vec->capacity * sizeof(int));
    if (vec->arr == NULL) {
      fprintf(stderr, "Pop failed");
      exit(EXIT_FAILURE);
    } 
  }
}

void clear(Vec *vec) {
  free(vec->arr);
  vec->capacity = 0;
  vec->data_size = 0;
}

int init_vec(Vec *vec) {
  vec->arr = calloc(INIT_CAPA, sizeof(int));
  if (!(vec->arr)) {
    return -1;
  }
  vec->data_size = 0;
  vec->capacity = INIT_CAPA;
  return 0;
}

int main(void) {
  Vec vec; // My vec
  init_vec(&vec);
  push(&vec, 2);
  push(&vec, 2);
  push(&vec, 2);
  printf("1st: %d\n", vec.arr[0]);
  printf("2nd: %d\n", vec.arr[1]);
  printf("3rd: %d\n", vec.arr[2]);

  printf("Size: %ld\n", vec.data_size);
  printf("Capacity: %ld\n", vec.capacity);

  clear(&vec);
  return 0;
}