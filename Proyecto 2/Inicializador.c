#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 5678
#define SEM_KEY 1234

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

    return 0;
}