#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY_CONTROL 6666
#define SEM_KEY_MEMORIA 777
#define SEM_KEY_ 888
#define SIZE_LINEA 60
#define N_SEMAPHORES 2
#define MAX_PROCESOS 100
#define SIZE_CONTROL sizeof(Control)

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
    Proceso procesos[MAX_PROCESOS];
    int count;
    int sem_id;
} Control;

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
        perror("Error en semctl (SETVAL)");
    }
}

int main(int argc, char *argv[])
{
    int shm_id,
        int lineas;
    int *mem;
    Control *control;
    char *shm_ptr;
    int sem_id_control, sem_id_memoria, sem_id_readers;
    ;
    int i;

    printf("Ingrese el numero de lineas que desea: ");
    scanf("%d", &lineas);

    // crear los semáforos

    // semaforo de control
    sem_id_control = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1)
    {
        perror("Error en semget");
    }

    // semáforo para la memoria compartida
    sem_id_memoria = semget(SEM_KEY + 1 + i, 1, IPC_CREAT | 0666);
    if (sem_ids[i] == -1)
    {
        perror("Error en semget");
    }

    // semaforo para readers
    sem_id_readers = semget(SEM_KEY2 + 1 + i, 1, IPC_CREAT | 0666);
    if (sem_reader_ids[i] == -1)
    {
        perror("Error en semget");
    }

    // inicializar los semáforos
    init_sem(sem_id_memoria, 1);
    init_sem(sem_id_readers, 1);

    // crear la memoria compartida
    shm_id = shmget(SHM_KEY, SIZE_CONTROL + SIZE_LINEA * lineas, IPC_CREAT | 0666); // Creacion de la memoria compartida
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

    // Escribir el control

    // Adjuntar el segmento de memoria compartida al espacio de direcciones del proceso
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Convertir el puntero a la memoria compartida a un puntero a una estructura Control
    control = (Control *)shm_ptr;

    // Escribir en la memoria compartida
    control->count = 0;
    control->sem_id = sem_id;

    // semaforo de control
    init_sem(control->sem_id, 1);

    // Separar el segmento de memoria compartida del espacio de direcciones del proceso
    shmdt(shm_ptr);

    printf("Se ha creado la memoria compartida con ID %d de %d bytes dividida en %d lineas.\n", shm_id, SIZE_LINEA * lineas, lineas);
    printf("Se han creado %d semaforos para la memoria.\n", N_SEMAPHORES * lineas);
    printf("Se ha creado un semaforo de control.\n");

    return 0;
}
