#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SEM_KEY 1234
#define SHM_KEY 5678

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    // Creamos un semáforo con 1 recurso disponible
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    union semun arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Creamos una zona de memoria compartida de 4096 bytes
    int shmid = shmget(SHM_KEY, 4096, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Adjuntamos la zona de memoria compartida a nuestro proceso
    char *shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Iteramos 10 veces para acceder a la sección crítica
    for (int i = 0; i < 10; i++) {
        // Esperamos a que el semáforo esté disponible
        struct sembuf sops[] = {{0, -1, 0}};
        if (semop(semid, sops, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        // Accedemos a la sección crítica (escribimos en memoria compartida)
        sprintf(shmaddr, "Proceso %d accediendo a la sección crítica", getpid());
        printf("%s\n", shmaddr);

        // Liberamos el semáforo (disponemos del recurso)
        struct sembuf sops2[] = {{0, 1, 0}};
        if (semop(semid, sops2, 1) == -1) {
            perror("semop");
            exit(EXIT_FAILURE);
        }

        // Esperamos un segundo antes de volver a acceder a la sección crítica
        sleep(1);
    }

    // Desvinculamos la zona de memoria compartida
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Borramos la zona de memoria compartida y el semáforo
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    if (semctl(semid, 0, IPC_RMID, arg) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
