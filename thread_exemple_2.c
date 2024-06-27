
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    // while (1) {

        printf("Philosopher %d is thinking.\n", id);
        // sleep(rand() % 2);

        // printf("Philosopher %d is hungry.\n", id);

        // Pick up left fork
        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d picked up left fork %d.\n", id, left);

        // Pick up right fork
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d picked up right fork %d.\n", id, right);

        // Eat
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2);

        // Put down right fork
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d put down right fork %d.\n", id, right);

        // Put down left fork
        pthread_mutex_unlock(&forks[left]);
        printf("Philosopher %d put down left fork %d.\n", id, left);
    // }

	pthread_exit(NULL); //???

}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    int i;

    // Initialize mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads (in practice, this will not be reached)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes (in practice, this will not be reached)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
