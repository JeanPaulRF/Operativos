#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define SHM_SIZE 1024
#define SHM_KEY 0x1234

int main() {
    // Crea la zona de memoria compartida
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Adjunta la zona de memoria compartida al espacio de direcciones del proceso
    void* shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void*)-1) {
        perror("shmat");
        exit(1);
    }

    // Crea un mutex
    pthread_mutex_t* mutex = (pthread_mutex_t*)shmaddr;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mutex, &attr);

    // Sección crítica
    while (1) {
        pthread_mutex_lock(mutex);
        printf("Sección crítica\n");
        sleep(1);
        pthread_mutex_unlock(mutex);
        sleep(1);
    }

    // Libera los recursos
    pthread_mutex_destroy(mutex);
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
