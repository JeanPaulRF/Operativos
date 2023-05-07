#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 5678
#define SEM_KEY 1234

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(int argc, char *argv[])
{
    int shmid;
    int lineas;
    int tamano_linea = 60;

    printf("Ingrese el numero de lineas que desea: ");
    scanf("%d", &lineas);

    shmid = shmget(SHM_KEY, tamano_linea * lineas, IPC_CREAT | 0666); // Creacion de la memoria compartida

    if (shmid < 0)
    {
        perror("Error con shmget");
        exit(1);
    }

    printf("Se ha creado la memoria compartida con ID %d y tamaño %d bytes.\n", shmid, tamano);

    // Creamos un semáforo con 1 recurso disponible
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    union semun arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    // Adjuntamos la zona de memoria compartida a nuestro proceso
    char *shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    return 0;
}