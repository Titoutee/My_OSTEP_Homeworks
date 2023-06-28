#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    char *term = argv[1];
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        char *line = NULL;
        char *linePtr = NULL;  // Pointer to keep track of the original allocated memory
        size_t buf_size = 0;
        while (getline(&line, &buf_size, fp) != -1) {
            linePtr = line;  // Update linePtr to the current value of line
            //printf("%p", linePtr);
            while (isspace((char)*line)) line++;
            if (strstr(line, term) != NULL) {
                printf("%s", line);
            }
            line = linePtr;  // Restore line to the original allocated memory
        }
        if (line != NULL) {
            free(line);
        }
        fclose(fp);
    }
    return 0;
}
