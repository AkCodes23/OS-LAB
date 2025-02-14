#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wrt = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;
int data = 0; 

void* reader(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&wrt);
        }
        pthread_mutex_unlock(&mutex);

        // Reading section
        printf("Reader read data: %d\n", data);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&wrt);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* writer(void* arg) {
    while(1) {
        pthread_mutex_lock(&wrt);

        // Writing section
        data++;
        printf("Writer wrote data: %d\n", data);

        pthread_mutex_unlock(&wrt);
    }
}

int main() {
    pthread_t r1, r2, w1;

    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&r2, NULL, reader, NULL);
    pthread_create(&w1, NULL, writer, NULL);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    return 0;
}

//gcc -o Q2 Q2.c -lpthread -lrt
//.Q2
