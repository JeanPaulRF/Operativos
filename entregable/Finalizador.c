#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SEM_KEY_CONTROL 6666
#define SEM_KEY_MEMORIA 7777
#define SEM_KEY_READERS 8888
#define SIZE_LINEA 36
#define N_SEMAPHORES 2
#define MAX_PROCESOS 30
#define SIZE_CONTROL (int)sizeof(Control)

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
    int lineas;
} Control;

int main()
{
    int shm_id;

    key_t key = ftok("memoria_compartida", 'R'); // Clave IPC única

    if (key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    shm_id = shmget(key, 0, 0);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    key_t key_control = ftok("memoria_compartida_control", 'R'); // Clave IPC única

    if (key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shm_id_control = shmget(key_control, 0, 0);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Obtener el identificador del conjunto de semáforos
    int semid_control = semget(SEM_KEY_CONTROL, 0, 0);
    if (semid_control == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    int semid_memoria = semget(SEM_KEY_MEMORIA, 0, 0);
    if (semid_memoria == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    int semid_readers = semget(SEM_KEY_READERS, 0, 0);
    if (semid_readers == -1)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Matar todos los procesos
    // kill(0, SIGTERM);

    // Borramos la zona de memoria compartida y el semáforo
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    
    if (shmctl(shm_id_control, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid_control, 0, IPC_RMID) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid_memoria, 0, IPC_RMID) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid_readers, 0, IPC_RMID) == -1)
    {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    printf("\nSe finalizo la memoria compartida con id %d.\n", shm_id);
    printf("Se finalizaron los 2 semaforos para la memoria con id %d y %d.\n", semid_memoria, semid_readers);
    printf("Se finalizo el semaforo con id %d del control de procesos.\n", semid_control);

    // Cerrar el archivo de la bitácora
    FILE *fp = fopen("bitacora.txt", "a");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    printf("Se cerro el archivo bitacora.txt.\n");

    return 0;
}
