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
#define SIZE_LINEA 36
#define N_SEMAPHORES 2
#define MAX_PROCESOS 50
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
    int count;
    int lineas;
    Proceso procesos[MAX_PROCESOS];
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
    int lineas;
    void *mem;
    Control *control;
    char *shm_ptr;
    int sem_id_control, sem_id_memoria, sem_id_readers;
    int memory_size;
    int i, j;

    printf("-------------BIENVENIDO AL INICIALIZADOR DEL SISTEMA-------------\n\n");

    printf("Ingrese el numero de lineas que desea para la memoria compartida: ");
    scanf("%d", &lineas);

    memory_size = SIZE_CONTROL + (SIZE_LINEA * lineas);
    
    //printf("%d\n", memory_size);

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
    
    //printf("key creada\n");

    // crear la memoria compartida
    shm_id = shmget(SHM_KEY, memory_size, IPC_CREAT | 0666); // Creacion de la memoria compartida
    if (shm_id < 0)
    {
        perror("Error con shmget memoria");
        exit(1);
    }
    
    //printf("ID: %d\n", shm_id);
    
    // Escribir el control

    // Adjuntar el segmento de memoria compartida al espacio de direcciones del proceso
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat escribir");
        exit(1);
    }
    
    //printf("Memoria adjuntada\n");

    // Convertir el puntero a la memoria compartida a un puntero a una estructura Control y mensaje
    control = (Control *)shm_ptr;
    Mensaje *mensajes = (Mensaje *)(shm_ptr + sizeof(Control));

    // Escribir en la memoria compartida
    control = malloc(sizeof(Control));
    control->count = 0;
    control->lineas = lineas;
    
    for (i = 0; i < MAX_PROCESOS; i++)
    {
        control->procesos[i].pid = 1;
        control->procesos[i].tipo = 0;
        control->procesos[i].estado = 0;
    }

    // Inicializar los bloques de las líneas
    for (i = 0; i < lineas; i++)
    {
	    mensajes[i].pid = 0;
	    mensajes[i].year = 0;
	    mensajes[i].month = 0;
	    mensajes[i].day = 0;
	    mensajes[i].hour = 0;
	    mensajes[i].minute = 0;
	    mensajes[i].second = 0;
	    mensajes[i].mensaje = 0;
    }

    // Separar el segmento de memoria compartida del espacio de direcciones del proceso
    if (shmdt(shm_ptr) == -1)
    {
        perror("shmdt");
        exit(1);
    }

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
    
    
    
    
    
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat escribir");
        exit(1);
    }

    // Convertir el puntero a la memoria compartida a un puntero a una estructura Control y mensaje
    control = (Control *)shm_ptr;
    Mensaje *mensajesa = (Mensaje *)(shm_ptr + sizeof(Control));

    // Escribir en la memoria compartida
    printf("count: %d\n", control->count);
    printf("lineas: %d\n", control->lineas);
    
    for (i = 0; i < MAX_PROCESOS; i++)
    {
    	printf("proceso pid: %d\n", control->procesos[i].pid);
    }

    // Inicializar los bloques de las líneas
    for (i = 0; i < lineas; i++)
    {
    	printf("linea pid: %d\n", mensajesa[i].pid);
    }

    // Separar el segmento de memoria compartida del espacio de direcciones del proceso
    if (shmdt(shm_ptr) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    
    


    printf("\nSe ha creado la memoria compartida con id %d de %d bytes dividida en %d lineas.\n", shm_id, SIZE_LINEA * lineas + SIZE_CONTROL, lineas);
    printf("Se han creado %d semaforos para acceder a la memoria con id %d y %d.\n", N_SEMAPHORES, sem_id_memoria, sem_id_readers);
    printf("Se ha creado un semaforo de control con id %d.\n", sem_id_control);

    return 0;
}
