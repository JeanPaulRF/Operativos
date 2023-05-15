#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY_CONTROL 6666
#define SEM_KEY_MEMORIA 7777
#define SEM_KEY_READERS 8888

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
    int semid_control = semget(SEM_KEY_CONTROL, 0, 0);
    if (semid_control == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    int semid_memoria = semget(SEM_KEY_MEMORIA, 0, 0);
    if (semid_memoria == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    int semid_readers = semget(SEM_KEY_READERS, 0, 0);
    if (semid_readers == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Matar todos los procesos
    kill(0, SIGTERM);

    // Desvinculamos la zona de memoria compartida
    if (shmdt(shmaddr) == -1)
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Borramos la zona de memoria compartida y el semáforo
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    if (semctl(semid_control, 0, IPC_RMID, arg) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid_memoria, 0, IPC_RMID, arg) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid_readers, 0, IPC_RMID, arg) == -1)
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
