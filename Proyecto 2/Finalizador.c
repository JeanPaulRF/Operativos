#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 5678
#define SEM_KEY 1234

int main()
{
    // Obtener el identificador del segmento de memoria compartida
    int shmid = shmget(SHM_KEY, 0, 0);
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Obtener el identificador del conjunto de semáforos
    int semid = semget(SEM_KEY, 0, 0);
    if (semid == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Matar todos los procesos
    kill(0, SIGTERM);

    // Liberar la memoria compartida
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    // Liberar el conjunto de semáforos
    if (semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Cerrar el archivo de la bitácora
    FILE *fp = fopen("bitacora.txt", "a");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    return 0;
}
