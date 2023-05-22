#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "Mensaje.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SEM_KEY_CONTROL 6666
#define SEM_KEY_MEMORIA 7777
#define SEM_KEY_READERS 8888
#define SIZE_LINEA 40
#define N_SEMAPHORES 2
#define MAX_PROCESOS 100
#define SIZE_CONTROL sizeof(Control)

typedef struct
{
    int pid;
    int tipo;   // 0 = reader, 1 = writer, 2 = reader egoista
    int estado; // 0 = bloqueado, 1 = dormido, 2 = ejecutando
} Proceso;

// estructura para el control de procesos
typedef struct
{
    Proceso procesos[MAX_PROCESOS];
    int count;
    int lineas;
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
    int shm_id;
    int shm_id_control;
    int lineas;
    char *mem;
    Control *control;
    char *shm_ptr;
    int sem_id_control, sem_id_memoria, sem_id_readers;
    int memory_size;
    int i, j;

    printf("-------------BIENVENIDO AL INICIALIZADOR DEL SISTEMA-------------\n\n");

    printf("Ingrese el numero de lineas que desea para la memoria compartida: ");
    scanf("%d", &lineas);

    memory_size = SIZE_LINEA * lineas;

    int fd = open("memoria_compartida", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd);

    key_t SHM_KEY = ftok("memoria_compartida", 'R');
    if (SHM_KEY == -1)
    {
        perror("ftok");
        exit(1);
    }

    // crear la memoria compartida
    shm_id = shmget(SHM_KEY, memory_size, IPC_CREAT | 0666); // Creacion de la memoria compartida
    if (shm_id < 0)
    {
        perror("Error con shmget memoria");
        exit(1);
    }
    
    //memoria control
    int fd2 = open("memoria_compartida_control", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd2 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd2);

    key_t SHM_KEY_control = ftok("memoria_compartida_control", 'R');
    if (SHM_KEY == -1)
    {
        perror("ftok");
        exit(1);
    }

    // crear la memoria compartida
    shm_id_control = shmget(SHM_KEY_control, SIZE_CONTROL, IPC_CREAT | 0666); // Creacion de la memoria compartida
    if (shm_id < 0)
    {
        perror("Error con shmget memoria");
        exit(1);
    }
    
    // Escribir el control

    // Adjuntar el segmento de memoria compartida al espacio de direcciones del proceso
    shm_ptr = shmat(shm_id_control, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat escribir");
        exit(1);
    }

    // Convertir el puntero a la memoria compartida a un puntero a una estructura Control
    control = (Control *)shm_ptr;

    // Escribir en la memoria compartida
    control->count = 0;
    control->lineas = lineas;

    // Separar el segmento de memoria compartida del espacio de direcciones del proceso
    shmdt(shm_ptr);

    // Adjuntar la memoria compartida al espacio de direcciones del proceso
    mem = shmat(shm_id, NULL, 0);
    if (mem == (char *)-1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    Mensaje *mensajes = (Mensaje *)(char *)mem;

    // Inicializar los bloques de las líneas
    for (i = 0; i < lineas; i++)
    {
          Mensaje mensaje = {0};
          mensajes[i] = mensaje;
          mensajes[i].linea = i;
    }

    // Separar el segmento de memoria compartida del espacio de direcciones del proceso
    shmdt(mem);

    // crear los semáforos

    // semaforo de control
    sem_id_control = semget(SEM_KEY_CONTROL, 1, IPC_CREAT | 0666);
    if (sem_id_control == -1)
    {
        perror("Error en semget control");
    }

    // semáforo para la memoria compartida
    sem_id_memoria = semget(SEM_KEY_MEMORIA, 1, IPC_CREAT | 0666);
    if (sem_id_memoria == -1)
    {
        perror("Error en semget memoria");
    }

    // semaforo para readers
    sem_id_readers = semget(SEM_KEY_READERS, 1, IPC_CREAT | 0666);
    if (sem_id_readers == -1)
    {
        perror("Error en semget readers");
    }

    // inicializar los semáforos
    init_sem(sem_id_memoria, 1);
    init_sem(sem_id_readers, 1);
    init_sem(sem_id_control, 1);
    

    printf("\nSe ha creado la memoria compartida con id %d de %d bytes dividida en %d lineas.\n", shm_id, SIZE_LINEA * lineas + SIZE_CONTROL, lineas);
    printf("Se han creado %d semaforos para acceder a la memoria con id %d y %d.\n", N_SEMAPHORES, sem_id_memoria, sem_id_readers);
    printf("Se ha creado un semaforo de control con id %d.\n", sem_id_control);

    return 0;
}
