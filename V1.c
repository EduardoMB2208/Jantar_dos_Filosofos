#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t *forks;
int N = 5;

void *philosopher(void *arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        // Pensar
        printf("Filósofo %d está pensando.\n", id);
        sleep(1);

        // Pegar garfos (pode causar deadlock)
        printf("Filósofo %d está pegando os garfos.\n", id);
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        // Comer
        printf("Filósofo %d está comendo.\n", id);
        sleep(1);

        // Liberar garfos
        printf("Filósofo %d está soltando os garfos.\n", id);
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }
    return NULL;
}
