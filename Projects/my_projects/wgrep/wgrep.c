#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char **grep(FILE *fp, char *term, size_t lines) {
    char *line = NULL;
    char *linePtr = NULL;  // Pointer to keep track of the original allocated memory
    size_t buf_size = 0;
    int c=0;

    char **strings = malloc(sizeof(char *) * lines);
    
    while (getline(&line, &buf_size, fp) != -1) {
        linePtr = line;  // Update linePtr to the current value of line
        //printf("%p", linePtr);
        while (isspace((char)*line)) line++;
        if (strstr(line, term) != NULL) {
            strings[c] = line;
            c++;
        }
        line = linePtr;  // Restore line to the original allocated memory
    }
    return strings;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    char *term = argv[1];

    int stdin_ = 0;
    if (argc == 2) stdin_ = 1;
    
    if (!stdin_) {
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (!fp) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            //
            
            //
            fclose(fp);
        }
    } else {
        
    }
    
    return 0;
}
