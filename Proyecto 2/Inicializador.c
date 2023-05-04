#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    int shmid;
    int lineas;
    int tamano_linea = 1024;

    printf("Ingrese el numero de lineas que desea: ");
    scanf("%d", &lineas);

    shmid = shmget(5678, tamano_linea * lineas, IPC_CREAT | 0666); // Creacion de la memoria compartida

    if (shmid < 0)
    {
        perror("Error con shmget");
        exit(1);
    }

    printf("Se ha creado la memoria compartida con ID %d y tamaño %d bytes.\n", shmid, tamano);

    return 0;
}
