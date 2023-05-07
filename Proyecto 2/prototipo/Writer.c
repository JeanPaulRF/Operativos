#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678; // clave de la memoria compartida

    // obtener el identificador de la memoria compartida
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    // asociar la memoria compartida al espacio de direcciones del proceso
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // escribir en la memoria compartida
    s = shm;
    *s++ = 'H';
    *s++ = 'o';
    *s++ = 'l';
    *s++ = 'a';
    *s++ = ',';
    *s++ = ' ';
    *s++ = 'm';
    *s++ = 'u';
    *s++ = 'n';
    *s++ = 'd';
    *s++ = 'o';
    *s++ = '.';
    *s++ = '.';
    *s++ = '.';
    *s = '\0';

    // leer de la memoria compartida
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');

    // liberar el espacio de direcciones del proceso
    if (shmdt(shm) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
