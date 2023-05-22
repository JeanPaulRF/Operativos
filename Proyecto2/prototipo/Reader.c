#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "Mensaje.h"

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

/* Parametros a mandar para el proceso */
typedef struct
{
    int pid;
    int tiempo_leer;
    int tiempo_dormir;
} parametrosLector;

// parametros globales memoria compartida
int shm_id;
int shm_id_control;
int semid_control;
int semid_memoria;
int lineas;
//Control *control;
//Mensaje *mensajes;

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

/* Leer el mensaje  */
Mensaje read_message(int pid)
{                     // recibe el id del proceso que lo crea
    Mensaje MS = {0}; // Todos los miembros inicializan en 0.

    time_t tiempoActual; // declaro variable
    time(&tiempoActual); // obtengo el tiempo

    struct tm *fechaHora = localtime(&tiempoActual);

    MS.pid = pid;
    MS.year = fechaHora->tm_year + 1900;
    MS.month = fechaHora->tm_mon + 1;
    MS.day = fechaHora->tm_mday;
    MS.hour = fechaHora->tm_hour;
    MS.minute = fechaHora->tm_min;
    MS.second = fechaHora->tm_sec;
    MS.mensaje = 1; // esta lleno

    return MS;
}

/* Describe el comportamiento de todo proceso lector */
void *preader(void *arg)
{
	char *memoria;
    parametrosLector *parametros = (parametrosLector *)arg;
    int id = parametros->pid;
    // printf("\n--> ID: %d\n", parametros->pid);

    int estado = 1; // 1 esta escribiendo, 0 esta dormido
    int pr_tiempo_leer = parametros->tiempo_leer;
    int pr_tiempo_dormir = 0;

    // Mensaje new_ms = create_message(id);	// se movio al for 

    // ciclo while(1)
    // si esta despierto busca una linea que contenga algo
    // si esta dormido, simplemente sleep
	memoria = shmat(shm_id_control, NULL, 0);
    if (memoria == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    Control *control = (Control *)memoria;

    sem_wait(semid_control);

    // Manejar datos de control
    control->procesos[id].estado = 2;

    // signal semaforo control
    sem_signal(semid_control);

    if (shmdt(memoria) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    while (1)
    {
        // printf("\n\n pw_tiempo_escribir : %d \n", pw_tiempo_escribir);
        // printf(" pw_tiempo_dormir : %d\n\n", pw_tiempo_dormir);

        if (pr_tiempo_leer > 0)
        {
            // comportamiento cuando esta despierto
            memoria = shmat(shm_id_control, NULL, 0);
            if (memoria == (char *)-1)
            {
                perror("shmat");
                exit(1);
            }
			
			Control *control = (Control *)memoria;
			
            // actualizar estado
            sem_wait(semid_control);

            // Manejar datos de control
            control->procesos[id].estado = 0;

            // signal semaforo control
            sem_signal(semid_control);

			if (shmdt(memoria) == -1)
            {
                perror("shmdt");
                exit(1);
            }
			
            // entra en memoria
			memoria = shmat(shm_id, NULL, 0);
            if (memoria == (char *)-1)
            {
                perror("shmat");
                exit(1);
            }

            Mensaje *mensajes = (Mensaje *)memoria;

            // wait semaforo memoria
            sem_wait(semid_memoria);

            // Extraer los datos de memoria
            for (int i = 0; i < lineas; i++)
            {
                Mensaje mensaje = mensajes[i];
				printf("lineas %d", lineas);
                if (mensaje.mensaje == 1)
                {
                    printf("\n\n--> Proceso ID: %d\n", mensaje.pid);
					printf("--> Fecha leída: %d-%02d-%02d\n", mensaje.year, mensaje.month, mensaje.day);
					printf("--> Hora leida: %02d:%02d:%02d\n", mensaje.hour, mensaje.minute, mensaje.second);
                }
            }

            // signal semaforo memoria
            sem_signal(semid_memoria);

            if (shmdt(memoria) == -1)
            {
                perror("shmdt");
                exit(1);
            }
			/*
			printf("Print fuera del for");
            printf("\n\n--> Proceso ID: %d\n", mensaje.pid);
            printf("--> Fecha leídal: %d-%02d-%02d\n", mensaje.year, mensaje.month, mensaje.day);
            printf("--> Hora leida: %02d:%02d:%02d\n", mensaje.hour, mensaje.minute, mensaje.second);*/
            // sleep(5);
            //  manda a avisar al control que esta despierto

            // resto 1 tiempo por accion
            pr_tiempo_leer = pr_tiempo_leer - 1;
        }
        else if (pr_tiempo_dormir > 0)
        {
            // comportamiento cuando esta dormido
            printf("----> ZZzzZZ \n");
            // sleep(5);
            //  manda a avisar al control que esta dormido

            // resto 1 tiempo por accion
            pr_tiempo_dormir = pr_tiempo_dormir - 1;
        }

        // Para el cambio de estado, y rellenar el tiempo.
        if (pr_tiempo_leer == 0 && estado == 1)
        {
            // si el tiempo de escribir se agoto y estoy en el estado de lectura
            // relleno el tiempo de dormir
            pr_tiempo_dormir = parametros->tiempo_dormir;
            estado = 0; // lo paso al estado de Descanso
			
			memoria = shmat(shm_id_control, NULL, 0);
            if (memoria == (char *)-1)
            {
                perror("shmat");
                exit(1);
            }

            Control *control = (Control *)memoria;

            sem_wait(semid_control);

            // Manejar datos de control
            control->procesos[id].estado = 1;

            // signal semaforo control
            sem_signal(semid_control);
			
			if (shmdt(memoria) == -1)
            {
                perror("shmdt");
                exit(1);
            }
        }
        else if (pr_tiempo_dormir == 0 && estado == 0)
        {
            // si el tiempo de dormir se agoto y estoy en el estado de Descanso
            // relleno el tiempo de leer
            pr_tiempo_leer = parametros->tiempo_leer;
            estado = 1; // lo paso al estado de lectura

			memoria = shmat(shm_id_control, NULL, 0);
            if (memoria == (char *)-1)
            {
                perror("shmat");
                exit(1);
            }

            Control *control = (Control *)memoria;

            sem_wait(semid_control);

            // Manejar datos de control
            control->procesos[id].estado = 2;

            // signal semaforo control
            sem_signal(semid_control);
			
			if (shmdt(memoria) == -1)
            {
                perror("shmdt");
                exit(1);
            }
        }
        sleep(1);
		// vista de la memoria
        char *memoria = shmat(shm_id, NULL, 0);
        if (memoria == (char *)-1)
        {
            perror("shmat");
            exit(1);
        }

        Mensaje *mensajes = (Mensaje *)memoria;
        
        // wait semaforo memoria
        sem_wait(semid_memoria);
        
        // Extraer los datos de memoria
        for (int i = 0; i < lineas; i++)
        {
            Mensaje mensaje = mensajes[i];
            printf("lineas %d", lineas);
            printf(" PID: %d\n Linea: %d\n Mensaje: %d\n", mensaje.pid, mensaje.linea, mensaje.mensaje);
            printf(" Fecha actual: %d-%02d-%02d\n", mensaje.year, mensaje.month, mensaje.day);
            printf(" Hora actual: %02d:%02d:%02d\n", mensaje.hour, mensaje.minute, mensaje.second);
        }

        // signal semaforo memoria
        sem_signal(semid_memoria);
        if (shmdt(memoria) == -1)
        {
            perror("shmdt");
            exit(1);
        }
    }

    // cuando finalize :
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int NL, SL, SD;
    /*
      NL significa Numero de Lectores
      SL siginifica Segundos de Lectura
      SD significa Segundos de Dormir
     */

    // Mensaje ms1; // para pruubas
    // ms1 = create_message(23987);

    printf("-------------BIENVENIDO AL PROGRAMA LECTOR DEL SISTEMA-------------\n\n");

    printf("Ingrese el numero de procesos lectores: ");
    scanf("%d", &NL);

    printf("Ingrese el numero segundos que leeran: ");
    scanf("%d", &SL);

    printf("Ingrese el numero segundos que dormiran ");
    scanf("%d", &SD);

    // id de los procesos
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
    
    key_t key_control = ftok("memoria_compartida_control", 'R'); // usar la misma clave que en el otro programa
    if (key_control == -1)
    {
        perror("ftok");
        exit(1);
    }

    shm_id_control = shmget(key_control, 0, 0666);
    if (shm_id_control == -1)
    {
        perror("shmget");
        exit(1);
    }

    semid_control = semget(SEM_KEY_CONTROL, 1, 0666);
    if (semid_control == -1)
    {
        perror("Error al acceder al semáforo control");
        exit(1);
    }

    semid_memoria = semget(SEM_KEY_MEMORIA, 1, 0666);
    if (semid_memoria == -1)
    {
        perror("Error al acceder al semáforo memoria");
        exit(1);
    }

	char *memoria = shmat(shm_id_control, NULL, 0);
    if (memoria == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    Control *control = (Control *)memoria;
	
    // wait semaforo control
    sem_wait(semid_control);

    // Extraer las lineas de control
    lineas = control->lineas;

    // signal semaforo control
    sem_signal(semid_control);

    if (shmdt(memoria) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    // fin memoria compartida

    /* // pruebas
    printf(" Numero de procesos: %d\n Segundos de escritura: %d\n Segundos de descanso: %d\n", NE, SE, SD);
    printf(" Fecha actual: %d-%02d-%02d\n", ms1.year, ms1.month, ms1.day);
    printf(" Hora actual: %02d:%02d:%02d\n", ms1.hour, ms1.minute, ms1.second);
    */
    // %02d es una especificacion formato, para un numero con menos de dos digitos, que rellene un 0

    /* Creacion de los threads */
    pthread_t hilos[NL];
    parametrosLector par_Reader[NL];

    for (int i = 0; i < NL; i++)
    {
        par_Reader[i].tiempo_leer = SL;
        par_Reader[i].tiempo_dormir = SD;

        /* Por aqui deberia registrar los procesos al Control */

        char *memoria = shmat(shm_id_control, NULL, 0);
        if (memoria == (char *)-1)
        {
            perror("shmat");
            exit(1);
        }

        control = (Control *)memoria;

        // wait semaforo control
        sem_wait(semid_control);

        // Manejar datos de control
        int n = control->count;
        par_Reader[i].pid = n;
        control->procesos[n].pid = n;
        control->procesos[n].estado = 1;
        control->procesos[n].tipo = 0;
        control->count = n + 1;

        // signal semaforo control
        sem_signal(semid_control);

        if (shmdt(memoria) == -1)
        {
            perror("shmdt");
            exit(1);
        }

        if (pthread_create(&hilos[i], NULL, preader, (void *)&par_Reader[i]) != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // los hilos no me funcionaban cuando los mandaba con &, ejemplo &hilos[i]
    for (int i = 0; i < NL; i++)
    {
        if (pthread_join(hilos[i], NULL) != 0)
        {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
