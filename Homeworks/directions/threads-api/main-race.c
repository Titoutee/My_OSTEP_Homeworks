#include <pthread.h>
#include <stdio.h>

#include "common_threads.h"

int balance = 0;
pthread_mutex_t mutex1  ;

void* worker(void* arg) {
    Mutex_lock(&mutex1);
    balance++;
    Mutex_unlock(&mutex1);
    return NULL;
}

int main(int argc, char *argv[]) {
    Mutex_init(&mutex1);
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    Mutex_lock(&mutex1);
    balance++;
    Mutex_unlock(&mutex1);
    Pthread_join(p, NULL);
    return 0;
}
