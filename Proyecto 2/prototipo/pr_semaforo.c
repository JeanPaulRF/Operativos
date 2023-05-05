#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int shmid;
    key_t key;
    char *shmaddr;
    sem_t *sem;

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

    // Crear el semáforo para controlar el acceso a la memoria compartida
    sem = sem_open("mysem", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Escribir bytes en la memoria compartida
    sem_wait(sem);
    sprintf(shmaddr, "¡Hola, memoria compartida!");
    sem_post(sem);

    // Imprimir el contenido de la memoria compartida
    sem_wait(sem);
    printf("Contenido de la memoria compartida: %s\n", shmaddr);
    sem_post(sem);

    // Desvincular el segmento de memoria compartida de nuestro espacio de direcciones
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Cerrar el semáforo y eliminarlo
    if (sem_close(sem) == -1) {
        perror("sem_close");
        exit(1);
    }
    if (sem_unlink("mysem") == -1) {
        perror("sem_unlink");
        exit(1);
    }

    return 0;
}
