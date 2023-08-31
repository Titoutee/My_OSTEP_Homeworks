#include "vector.h"
#include "stdio.h"
#include "stdlib.h"

#define INIT_CAPA 1

void vec_push(Vec *vec, char elt) {
  if (vec->data_size==vec->capacity) { // We have consumed all the space beforehand allocated mem
    vec->capacity *= 2; // Efficiency wants that we double the capacity
    vec->arr = (char *) realloc(vec->arr, vec->capacity * sizeof(char)); // We realloc the vector with new capacity
  }
  vec->arr[vec->data_size++] = elt; // We add the given elt and increment data_size
}

void vec_pop(Vec *vec) {
  //char popped = vec->arr[vec->data_size--];
  if (vec->data_size <= vec->capacity/4) {
    vec->capacity /= 2;
    vec->arr = realloc(vec->arr, vec->capacity * sizeof(char));
    if (vec->arr == NULL) {
      fprintf(stderr, "Pop failed");
      exit(EXIT_FAILURE);
    } 
  }
}

int init_vec(Vec *vec) {
  vec->arr = calloc(INIT_CAPA, sizeof(char));
  if (!(vec->arr)) {
    return -1;
  }
  vec->data_size = 0;
  vec->capacity = INIT_CAPA;
  return 0;
}

char *inner(Vec *vec) {
  return vec->arr; //Be careful with lifetimes! (this should not outlive the vec instance!)
}