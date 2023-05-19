#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include "Mensaje.h"

#define SEM_KEY_CONTROL 6666
#define SEM_KEY_MEMORIA 7777
#define SEM_KEY_READERS 8888
#define SIZE_LINEA 40
#define N_SEMAPHORES 2
#define MAX_PROCESOS 100
#define SIZE_CONTROL sizeof(Control)

typedef struct {
    int pid;
    int tipo;   // 0 = reader, 1 = writer, 2 = reader egoista
    int estado; // 0 = bloqueado, 1 = dormido, 2 = ejecutando
} Proceso;

// estructura para el control de procesos
typedef struct {
    Proceso procesos[MAX_PROCESOS];
    int count;
    int lineas;
} Control;

// función auxiliar para inicializar un semáforo
void init_sem(int sem_id, int val) {
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;

    arg.val = val;

    if (semctl(sem_id, 0, SETVAL, arg) == -1) {
        perror("Error en semctl (SETVAL)");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int shm_id;
    void *mem;
    Control *control;
    char *shm_ptr;
    int sem_id_control, sem_id_memoria, sem_id_readers;
    int memory_size;
    int i, j;

    if (argc < 4) {
        printf("Uso: ./reader_egoista <cantidad_lectores_egoistas> <tiempo_lectura> <tiempo_dormir>\n");
        return 1;
    }

    int cantidad_lectores_egoistas = atoi(argv[1]);
    int tiempo_lectura = atoi(argv[2]);
    int tiempo_dormir = atoi(argv[3]);

    key_t SHM_KEY = ftok("memoria_compartida", 'R');
    if (SHM_KEY == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Obtener el ID de la memoria compartida
    shm_id = shmget(SHM_KEY, 0, 0);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Adjuntar la memoria compartida al espacio de direcciones del proceso
    mem = shmat(shm_id, NULL, 0);
    if (mem == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    Mensaje *mensajes = (Mensaje *)mem;

    // Obtener el ID de los semáforos
    sem_id_readers = semget(SEM_KEY_READERS, 0, 0);
    if (sem_id_readers == -1) {
        perror("semget readers");
        exit(EXIT_FAILURE);
    }

    // Generar el valor inicial del semáforo readers
    init_sem(sem_id_readers, 1);

    // Generar la semilla para la generación de números aleatorios
    srand(time(NULL));

    // Variables para controlar el número de readers egoístas consecutivos
    int consecutivo_egoistas = 0;
    int max_consecutivo_egoistas = 3;

    while (1) {
        // Bloquear el semáforo readers para asegurar acceso exclusivo
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(sem_id_readers, &sem_op, 1);

        // Verificar si se alcanzó el límite de readers egoístas consecutivos
        if (consecutivo_egoistas >= max_consecutivo_egoistas) {
            // Desbloquear el semáforo readers
            sem_op.sem_op = 1;
            semop(sem_id_readers, &sem_op, 1);

            // Esperar un tiempo antes de volver a intentar acceder
            sleep(tiempo_dormir);
            continue;
        }

        // Elegir una entrada aleatoria en la memoria compartida
        int entrada_aleatoria = rand() % control->lineas;

        // Leer el mensaje de la entrada seleccionada
        Mensaje mensaje = mensajes[entrada_aleatoria];

        // Verificar si la entrada tiene un mensaje
        if (mensaje.mensaje == 1) {
            // Actualizar el estado de la entrada como vacía
            mensajes[entrada_aleatoria].mensaje = 0;

            // Incrementar el contador de lectores egoístas consecutivos
            consecutivo_egoistas++;

            // Desbloquear el semáforo readers
            sem_op.sem_op = 1;
            semop(sem_id_readers, &sem_op, 1);

            // Leer el mensaje
            printf("Lector egoísta (PID: %d) - Mensaje: PID: %d, Fecha: %d-%d-%d %d:%d:%d, Línea: %d\n",
                   getpid(), mensaje.pid, mensaje.year, mensaje.month, mensaje.day, mensaje.hour,
                   mensaje.minute, mensaje.second, mensaje.linea);

            // Esperar el tiempo de lectura
            sleep(tiempo_lectura);

            // Reiniciar el contador de lectores egoístas consecutivos
            consecutivo_egoistas = 0;
        } else {
            // Desbloquear el semáforo readers
            sem_op.sem_op = 1;
            semop(sem_id_readers, &sem_op, 1);
        }
    }

    // Desasociar la memoria compartida
    shmdt(mem);

    return 0;
}
