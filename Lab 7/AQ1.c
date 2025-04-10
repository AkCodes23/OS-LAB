#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Philosopher states
#define THINKING 0
#define HUNGRY   1
#define EATING   2

int state[NUM_PHILOSOPHERS];
sem_t mutex;
sem_t sem[NUM_PHILOSOPHERS];

void test(int i) {
    if (state[i] == HUNGRY &&
        state[(i + 4) % 5] != EATING &&
        state[(i + 1) % 5] != EATING) {

        state[i] = EATING;
        sleep(1); // simulate eating
        printf("Philosopher %d takes forks %d and %d\n", i, (i + 4) % 5, i);
        printf("Philosopher %d is Eating\n", i);
        sem_post(&sem[i]);
    }
}

void take_forks(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is Hungry\n", i);
    test(i);
    sem_post(&mutex);
    sem_wait(&sem[i]); // wait if unable to eat
    sleep(1);
}

void put_forks(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\n", i, (i + 4) % 5, i);
    printf("Philosopher %d is Thinking\n", i);
    test((i + 4) % 5);
    test((i + 1) % 5);
    sem_post(&mutex);
}

void* philosopher(void* num) {
    int i = *(int*)num;

    while (1) {
        sleep(1); // thinking
        take_forks(i);
        sleep(2); // eating
        put_forks(i);
    }

    return NULL;
}

int main() {
    pthread_t thread_id[NUM_PHILOSOPHERS];
    int philosophers[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&sem[i], 0, 0);
        philosophers[i] = i;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
        printf("Philosopher %d is Thinking\n", i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}
