#include "stdlib.h"
#include <stdio.h>

#define BUFF_LENGTH 1024

int main(int argc, char *argv[]) {
  for (int arg_c = 1; arg_c < argc; arg_c++) {
    FILE *fp = fopen(argv[arg_c], "r");
    if (fp == NULL) {
      fprintf(stderr, "wcat: cannot open file\n");
      exit(EXIT_FAILURE);
    }
    char content[BUFF_LENGTH];
    while(fgets(content, BUFF_LENGTH, fp) != NULL) {
        printf("%s", content);
    }
    fclose(fp);
  }
  return 0;
}
