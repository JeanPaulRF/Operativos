#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 9999
#define SHM_SIZE sizeof(struct ejemplo) // tamaño de la estructura

typedef struct
{
    int pid_logico;
    int pid_fisico;
    int tipo;   // 0 = reader, 1 = writer, 2 = reader egoista
    int estado; // 0 = bloqueado, 1 = dormido, 2 = ejecutando
} Proceso;

// estructura para el control de procesos
typedef struct
{
    Proceso[MAX_PROCESOS] * procesos;
    int count;
    int sem_id;
} Control;

int main()
{
    int shm_id;
    key_t key = ftok("memoria_compartida", SHM_KEY); // usar la misma clave que en el otro programa
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    shm_id = shmget(key, SHM_SIZE, 0666);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    struct Control *control = (struct Control *)shmat(shm_id, NULL, 0);
    if (control == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // leer de control
    printf("Leyendo estructura desde la memoria compartida:\n");
    printf("a = %d\nb = %s\n", control->count, control->sem_id);

    if (shmdt(control) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
