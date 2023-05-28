#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"
#include "fcntl.h"
#include <fcntl.h>

#define SIZE 9

int main(void) {
    printf("Beginning of job, starting with parent process (pid: %d)\n", getpid());
    int p[2];
    int child_pid = 0;

    if (pipe(p) < 0) {
        exit(EXIT_FAILURE);
    }
    int rc = fork(); // Fork happens here first time
    
    if (rc<0) {
        printf("Error while creating child process");
        exit(1);
    }
    else if (rc == 0) { // First hild runs
        printf("Hello from child process here (pid: %d)\n", getpid());
        write(p[1], "Hey cat!", SIZE);
        child_pid = getpid();
        printf("End of child process run!\n");
    } else { // Back to parent control
        waitpid(child_pid, NULL, 0); // Child runs first hence
        printf("Hello from parent here (pid: %d)\n", getpid());
        char inbuf[SIZE];
        int bytes = read(p[0], inbuf, SIZE);
        if (bytes > 0) {
            printf("%s\n", inbuf);
        }
        else {
            exit(EXIT_FAILURE);
        }
        printf("Parent: I read all of the contents!\n");
    }
}