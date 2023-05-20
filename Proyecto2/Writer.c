#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "Mensaje.h"

#define SHM_KEY 9999
#define SEM_KEY 1234
#define SEM_KEY2 5678

/* Parametros a mandar para el proceso */
typedef struct {
    int pid;
    int tiempo_escribir;
    int tiempo_dormir;
} parametrosEscritor;

/* Escribe el mensaje, toma el tiemo y todo */
Mensaje create_message(int pid){ //recibe el id del proceso que lo crea
    Mensaje MS = {0}; // Todos los miembros inicializan en 0.

    time_t tiempoActual; // declaro variable
    time(&tiempoActual); // obtengo el tiempo

    struct tm* fechaHora = localtime(&tiempoActual);

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

/* Describe el comportamiento de todo proceso escritor */
void* pwriter(void* arg){
    parametrosEscritor* parametros = (parametrosEscritor*)arg;
    int id = parametros->pid;
    int estado = 0; // 1 esta escribiendo, 0 esta dormido
    Mensaje new_ms = create_message(id);

    printf(" Proceso ID: %d\n\n", new_ms.pid);
    printf(" Fecha actual: %d-%02d-%02d\n", new_ms.year, new_ms.month, new_ms.day);
    printf(" Hora actual: %02d:%02d:%02d\n", new_ms.hour, new_ms.minute, new_ms.second);
    // ciclo while(1)
    // si esta despierto busca una linea vacia
    // si esta dormido, simplemente sleep

    // cuando finalize : 
    pthread_exit(NULL);

}

int main(int argc, char *argv[])
{
    int NE, SE, SD;
    /*
      NE significa Numero de Escritores
      SE siginifica Segundos de Escritura
      SD significa Segundos de Dormir
     */

    Mensaje ms1;
    int opcion = 0;
    int bandera01 = 1;

    ms1 = create_message(23987);

    printf("-------------BIENVENIDO AL PROGRAMA ESCRITOR DEL SISTEMA-------------\n\n");

    printf("Ingrese el numero de procesos escritores: ");
    scanf("%d", &NE);

    printf("Ingrese el numero segundos que escribiran: ");
    scanf("%d", &SE);

    printf("Ingrese el numero segundos que dormiran ");
    scanf("%d", &SD);

    printf(" Numero de procesos: %d\n Segundos de escritura: %d\n Segundos de descanso: %d\n", NE, SE, SD);
    printf(" Fecha actual: %d-%02d-%02d\n", ms1.year, ms1.month, ms1.day);
    printf(" Hora actual: %02d:%02d:%02d\n", ms1.hour, ms1.minute, ms1.second);
    // %02d es una especificacion formato, para un numero con menos de dos digitos, que rellene un 0

    /* Creacion de los threads */
    pthread_t hilos[NE];

    for(int i = 0; i < NE; i++){

        parametrosEscritor par_Writer;
        par_Writer.pid = 400 + i;
        par_Writer.tiempo_escribir = SE;
        par_Writer.tiempo_dormir = SD;

        if(pthread_create(&hilos[i], NULL, pwriter, (void*)&par_Writer ) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    printf("\nVa por aqui 1\n");
    for(int i = 0; i < NE; i++){
        printf("\nVa por aqui 2\n");
        if(pthread_join(hilos[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
        printf("\nVa por aqui 3\n");
    }
    
    /* Por aqui deberia registrar los procesos al Control */

    /* Un pequeño menu para ver el progreso de los escritores */
    
    while(bandera01 == 1){
        printf("\n--> Opciones: \n");
        printf("----> 0) Exit: \n");
        printf("----> 1) Mostrar Estado: \n");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 0:
            bandera01 = 0; //salgo del menu
            // cierro los threads
            break;
        
        default:
            break;
        }
    }

    return 0;
}

/*
while (1)
{
    sem_wait(semA);
    // Acceder a la memoria compartida para el tipo A
    sem_post(semA);
    // Realizar otras tareas
}*/
