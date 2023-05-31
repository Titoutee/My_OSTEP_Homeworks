#define _GNU_SOURCE 
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "fcntl.h"
#include "unistd.h"
#include "sched.h" 

#define SAMPLES 1000

double avg_time_syscall(int samples, size_t n) {
    struct timeval t1;
    struct timeval t2;
    int fd;
    long delta = 0;
    char *buf;

    for(int _=0; _<samples; _++) {
        fd = open("test.txt", O_RDONLY|O_CREAT);
        if (fd == -1) {
            perror("Error openning filz");
            exit(EXIT_FAILURE);
        }

        gettimeofday(&t1, NULL);
        read(fd, buf, n); // Simple sys call
        gettimeofday(&t2, NULL);
        delta = delta + ((long) t2.tv_sec*1000000+t2.tv_usec)-((long) t1.tv_sec*1000000+t1.tv_usec);
        //printf("delta: %ld microseconds\n", delta);
        close(fd);
    }

    return (double) delta / (double) samples; // Mean
}

int main(int argc, char *argv[]) {
    //Sys call
    printf("Sys call with a call to \"open\" mean time (0 bytes reading) : %.3f microseconds\n", avg_time_syscall(SAMPLES, 0));
    
}



/*
 * Measure the costs of a system call, by repeatedly performing a nbyte-byte fread.
 * @param samples, the number of measurements taken
 * @param nbyte, the number of bytes to read
 * @return the average time to perform the syscall in microseconds.
 */