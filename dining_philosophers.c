#include <stdio.h> 
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];
pthread_t philosopher[N];
int phil_num[N];

void *philosopher_func(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking\n", id + 1);
        sleep(2);

        printf("Philosopher %d is hungry\n", id + 1);
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id + 1);
        sleep(2);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        printf("Philosopher %d finished eating and put down chopsticks 🥢\n", id + 1);
    }
}

int main() {
    int i;

    for (i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
        phil_num[i] = i;
    }

    for (i = 0; i < N; i++) {
        pthread_create(&philosopher[i], NULL, philosopher_func, &phil_num[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(philosopher[i], NULL);
    }

    for (i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0; 
}
