#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "Mensaje.h"
#include "Reader.c"
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
    int lineas;
	int cantLectores;
    void *mem;
    Control *control;
    char *shm_ptr;
    int sem_id_control, sem_id_memoria, sem_id_readers;
    int memory_size;
    int i, j;

    printf("-------------BIENVENIDO AL INICIALIZADOR DEL SISTEMA-------------\n\n");

    printf("Ingrese el numero de lineas que desea para la memoria compartida: ");
    scanf("%d", &lineas);
	
	memory_size = SIZE_CONTROL + SIZE_LINEA * lineas;
	
	printf("Ingrese el numero de procesos lectores: ");
	scanf("%d", &cantLectores); 	

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

    // Adjuntar la memoria compartida al espacio de direcciones del proceso
    mem = shmat(shm_id, NULL, 0);
    if (mem == (void *)-1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    Mensaje *mensajes = (Mensaje *)mem;

    // Inicializar los bloques de las líneas
    for (i = 0; i < lineas; i++)
    {
        for (j = 0; j < SIZE_LINEA / sizeof(int); j++)
        {
            Mensaje mensaje = {0};
            mensajes[i] = mensaje;
        }
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

    // Escribir el control

    // Adjuntar el segmento de memoria compartida al espacio de direcciones del proceso
    shm_ptr = shmat(shm_id, NULL, 0);
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

	// Crear procesos lectores
    for (int i = 0; i < cantLectores; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // Código del proceso hijo (lector)
            reader(i, 2, 2, SIZE_LINEA); // Ejemplo de tiempo de lectura y tiempo de dormir
            exit(0);
        }
    }
	
	// Esperar a que todos los procesos lectores finalicen
    for (int i = 0; i < cantLectores; i++) {
        wait(NULL);
    }

    // Separar el segmento de memoria compartida del espacio de direcciones del proceso
    shmdt(shm_ptr);

    printf("\nSe ha creado la memoria compartida con id %d de %d bytes dividida en %d lineas.\n", shm_id, SIZE_LINEA * lineas + SIZE_CONTROL, lineas);
    printf("Se han creado %d semaforos para acceder a la memoria con id %d y %d.\n", N_SEMAPHORES, sem_id_memoria, sem_id_readers);
    printf("Se ha creado un semaforo de control con id %d.\n", sem_id_control);

    return 0;
}
