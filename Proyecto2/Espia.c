#include <stdio.h>
#include <stdlib.h>
#include "Mensaje.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY_CONTROL 6666
#define SEM_KEY_MEMORIA 7777
#define MAX_PROCESOS 100
#define SIZE_CONTROL (int)sizeof(Control) // tamaño de la estructura

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

int shm_id;
int semid_control;
int semid_memoria;
int lineas;
int opcion;
char *tipos[] = {"Reader", "Writer", "Reader Egoista"};
char *estados[] = {"Bloqueado", "Dormido", "Ejecutando"};

// Función para realizar la operación wait (P) en el semáforo
void sem_wait(int sem_id)
{
    struct sembuf sb;
    sb.sem_num = 0; // Número del semáforo en el conjunto
    sb.sem_op = -1; // Operación wait (P)
    sb.sem_flg = 0; // Sin banderas adicionales

    semop(sem_id, &sb, 1);
}

// Función para realizar la operación signal (V) en el semáforo
void sem_signal(int sem_id)
{
    struct sembuf sb;
    sb.sem_num = 0; // Número del semáforo en el conjunto
    sb.sem_op = 1;  // Operación signal (V)
    sb.sem_flg = 0; // Sin banderas adicionales

    semop(sem_id, &sb, 1);
}

void estado_memoria()
{
    void* memoria = shmat(shm_id, NULL, 0);
    if (memoria == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }
    
    Mensaje* mensajes = (Mensaje*)memoria;

    // wait semaforo memoria
    sem_wait(semid_memoria);

    // Extraer los datos de memoria
    for (int i = 0; i < lineas; i++)
    {
        Mensaje* mensaje = &(mensajes[i]);

        if (mensaje == NULL)
            printf("Linea %d vacia\n", i);
        else
        {
            printf("Linea: %d - ", i);
            printf("PID: %d - ", mensaje->pid);
            printf("Fecha: %d/%d/%d - ", mensaje->day, mensaje->month, mensaje->year);
            printf("Hora: %d:%d:%d\n", mensaje->hour, mensaje->minute, mensaje->second);
        }
    }

    // signal semaforo memoria
    sem_signal(semid_memoria);

    if (shmdt(memoria) == -1)
    {
        perror("shmdt");
        exit(1);
    }
	menu();
    return;
}

void estado_procesos(int tipo)
{
    Control *control = (struct Control *)shmat(shm_id, NULL, 0);
    if (control == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // wait semaforo control
    sem_wait(semid_control);

    // Extraer los datos de control
    int count = control->count;
    Proceso *procesos = control->procesos;

    // signal semaforo control
    sem_signal(semid_control);

    if (shmdt(control) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    // Imprimir los datos
    for (int i = 0; i < count; i++)
    {
        if (tipo < 0 || procesos[i].tipo == tipo)
        {
            printf("PID: %d  ", procesos[i].pid);
            printf("TIPO: %d  ", tipos[procesos[i].tipo]);
            printf("ESTADO: %d\n", estados[procesos[i].estado]);
        }
    }
	menu();

    return;
}

void menu()
{
    printf("\n------------BIENVENIDO AL PROGRAMA ESPIA DEL SISTEMA------------\n\n");

    printf("1. Ver estado de la memoria compartida\n");
    printf("2. Ver estado de los Writers\n");
    printf("3. Ver estado de los Readers\n");
    printf("4. Ver estado de los Readers Egoistas\n");
    printf("5. Ver estado de todos los procesos\n");
    printf("6. Salir\n");
    printf("\nElija una opcion: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        printf("\nEstado de la memoria compartida:\n\n");
        estado_memoria();
        break;
    case 2:
        printf("\nEstado de los Writers:\n\n");
        estado_procesos(1);
        break;
    case 3:
        printf("\nEstado de los Readers:\n\n");
        estado_procesos(0);
        break;
    case 4:
        printf("\nEstado de los Readers Egoistas:\n\n");
        estado_procesos(2);
        break;
    case 5:
        printf("\nEstado de todos los procesos:\n\n");
        estado_procesos(-1);
        break;
    default:
        printf("\nSaliendo del programa...\n\n");
        break;
    }
    return;
}

int main()
{
    key_t key = ftok("memoria_compartida", 'R'); // usar la misma clave que en el otro programa
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    shm_id = shmget(key, 0, 0666);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    // wait semaforo control
    sem_wait(semid_control);

    Control *control = (struct Control *)shmat(shm_id, NULL, 0);
    if (control == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Extraer las lineas de control
    lineas = control->lineas;

    // signal semaforo control
    sem_signal(semid_control);

    if (shmdt(control) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    semid_control = semget(SEM_KEY_CONTROL, 1, 0666);
    if (semid_control == -1)
    {
        perror("Error al acceder al semáforo control");
        exit(1);
    }

    semid_memoria = semget(SEM_KEY_MEMORIA, 1, 0666);
    if (semid_control == -1)
    {
        perror("Error al acceder al semáforo memoria");
        exit(1);
    }

    menu();

    return 0;
}
