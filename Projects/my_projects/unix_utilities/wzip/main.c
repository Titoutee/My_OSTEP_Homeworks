#include "stdio.h"
#include "stdlib.h"

#define BUFFER_SIZE 512

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    int streak = 0;
    char current_c;
    char buff[BUFFER_SIZE];

    for(int file = 1; file < argc; file++) {
        FILE *fp = fopen(argv[file],"r");
        if(fp == NULL) {
			printf("wzip: cannot open file\n");
			exit(EXIT_FAILURE);
		}
        
        current_c = fgetc(fp); // Will never be in buffer
        streak++;

        while(fgets(buff, sizeof(buff), fp) != NULL) {
            for(int i = 0; buff[i] != '\0'; i++) {
                if (buff[i] == current_c) {
                    streak++;
                } else {
                    fwrite(&streak, sizeof(int), 1, stdout);
                    fwrite(&current_c, sizeof(char), 1, stdout);
                    current_c = buff[i];
                    streak = 1;
                }
            }
        }
        fclose(fp);
    }

    fwrite(&streak, sizeof(int), 1, stdout);
    fwrite(&current_c, sizeof(char), 1, stdout); 
    exit(0);
}