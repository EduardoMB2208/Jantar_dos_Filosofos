#include <pthread.h>     // Biblioteca para threads (mutex, criação de threads)
#include <semaphore.h>   // Biblioteca de Semaforos
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 5


sem_t limitante;          // Semáforo para limitar filósofos
pthread_mutex_t forks[N]; // Mutexes para garfos

void *philosopher(void *arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        // Pensar
        printf("Filósofo %d está pensando.\n", id);
        sleep(1);

        // Espera receber o sinal de controle do semaforo 
        sem_wait(&limitante);


        // Pegar garfos (pode causar deadlock)
        printf("Filósofo %d está pegando os garfos.\n", id);
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        // Comer
        printf("Filósofo %d está comendo.\n", id);
        sleep(2);

        // Liberar garfos
        printf("Filósofo %d está soltando os garfos.\n", id);
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
        sem_post(&limitante);
    }
    return NULL;
}

//ainda precisar inicializar as threads e mutexes no main.
