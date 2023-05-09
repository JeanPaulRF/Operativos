#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 9999
#define SEM_KEY 1234
#define SEM_KEY2 5678
#define SIZE_LINEA 60
#define N_SEMAPHORES 2

// función auxiliar para inicializar un semáforo
void init_sem(int sem_id, int val)
{
    union semun
    {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;

    arg.val = val;

    if (semctl(sem_id, 0, SETVAL, arg) == -1)
    {
        error("Error en semctl (SETVAL)");
    }
}

int main(int argc, char *argv[])
{
    int shm_id;
    int lineas;
    int *mem;

    printf("Ingrese el numero de lineas que desea: ");
    scanf("%d", &lineas);

    int sem_ids[lineas];
    int sem_reader_ids[lineas];

    // crear los semáforos

    // semáforos para la memoria compartida
    for (i = 0; i < lineas; i++)
    {
        sem_ids[i] = semget(SEM_KEY + i, 1, IPC_CREAT | 0666);
        if (sem_ids[i] == -1)
        {
            error("Error en semget");
        }
    }

    // semaforos para readers
    for (i = 0; i < lineas; i++)
    {
        sem_reader_ids[i] = semget(SEM_KEY2 + i, 1, IPC_CREAT | 0666);
        if (sem_reader_ids[i] == -1)
        {
            error("Error en semget");
        }
    }

    // inicializar los semáforos

    // semáforos para la memoria compartida
    for (i = 0; i < lineas; i++)
    {
        init_sem(sem_ids[i], 1);
    }

    // semaforos para readers
    for (i = 0; i < lineas; i++)
    {
        init_sem(sem_reader_ids[i], 1);
    }

    // crear la memoria compartida
    shm_id = shmget(SHM_KEY, SIZE_LINEA * lineas, IPC_CREAT | 0666); // Creacion de la memoria compartida
    if (shm_id < 0)
    {
        perror("Error con shmget");
        exit(1);
    }

    // inicializar la memoria compartida
    for (i = 0; i < lineas; i++)
    {
        mem[i] = 0;
    }

    printf("Se ha creado la memoria compartida con ID %d de %d bytes dividida en %d lineas.\n", shm_id, SIZE_LINEA * lineas, lineas);
    printf("Se han creado %d semaforos.\n", N_SEMAPHORES * lineas);

    return 0;
}