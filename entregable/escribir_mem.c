#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    key_t key;
    char *shmaddr;

    // Generar una clave única para el segmento de memoria compartida
    key = ftok(".", 'R');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Crear el segmento de memoria compartida con shmget
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Adjuntar el segmento de memoria compartida a nuestro espacio de direcciones
    shmaddr = (char *)shmat(shmid, (void *)0, 0);
    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Escribir bytes en la memoria compartida
    sprintf(shmaddr, "¡Hola, memoria compartida!");

    // Imprimir el contenido de la memoria compartida
    printf("Contenido de la memoria compartida: %s\n", shmaddr);

    // Desvincular el segmento de memoria compartida de nuestro espacio de direcciones
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
