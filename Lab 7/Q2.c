#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t resource;       // Semaphore to control access to the resource
pthread_mutex_t mutex; // Mutex to protect read_count
int read_count = 0;    // Number of readers accessing the resource

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&resource); // First reader locks the resource
    }
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d is reading the resource.\n", reader_id);
    sleep(1); // Simulate reading time

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&resource); // Last reader unlocks the resource
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    sem_wait(&resource); // Writer locks the resource

    // Writing section
    printf("Writer %d is writing to the resource.\n", writer_id);
    sleep(1); // Simulate writing time

    sem_post(&resource); // Writer unlocks the resource
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    sem_init(&resource, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create reader and writer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader and writer threads
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&resource);
    pthread_mutex_destroy(&mutex);

    return 0;
}
