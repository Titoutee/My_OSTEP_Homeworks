#include "stdio.h"
#include "stdlib.h"
#include <stddef.h>

#define BUFFER_SIZE 512

char *string_with_n_chars(char pred, size_t n) {
  char *string = malloc((n + 1) * sizeof(char));
  for (int i = 0; i < n; i++) {
    string[i] = pred;
  }
  string[n] = '\0'; // Considered as a string
  return string;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(EXIT_FAILURE);
  }

  int amount = 0;
  char c = (char)0;

  for (int file = 1; file < argc; file++) {
    FILE *fp = fopen(argv[file], "r");
    if (fp == NULL) {
      printf("wunzip: cannot open file\n");
      exit(EXIT_FAILURE);
    }

    while (fread(&amount, sizeof(int), 1, fp) != EOF &&
           (c = fgetc(fp)) != EOF) { // Assumes atomic amount-char duets (if
                                     // char misses at the end, just skips)
      char *string = string_with_n_chars(c, amount);
      printf("%s", string);
    }
    fclose(fp);
  }
  exit(0);
}