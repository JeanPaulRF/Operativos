#include <stdio.h>
#include <stdlib.h>
#include "proceso.h"

/* 
	El Job Scheduler debe;
-> Recibir los mesajes del cliente { Burst(x), Prioridad(Y) } y transformarlo en un Proceso, dandole un PID.
-> Retornar un mensaje al cliente con el PID del proceso.
-> Crear una cola de READY
-> Recibir procesos sin terminar, para volver a ponerlos en la cola de READY

*/
typedef struct 
{
	unsigned int cont_PID;
	unsigned int cant_JOB;
	unsigned int index;
	Proceso *READY; 
	
} JobScheduler;

// crear la estructura
struct* JobScheduler new_JobScheduler(){
	JobScheduler *new_JS;
	new_JS->cont_PID = 1; // 0 a 4294967295
	new_JS->cant_JOB = 50;
	new_JS->index = 0;
	new_JS->READY = (Proceso *) malloc(50); // arreglo base con capacidad para 50 procesos
	return new_JS;
}

// Funcion para agrandar la cola READY
/*
void agrandar_cola_READY(struct JobScheduler *JS){
	// el 70 seria el total ya aumentada
	// Reallocating memory
	JS->READY = (Proceso *) realloc(READY, 70); 
}
*/

// insertar un nuevo proceso
/*
void insert_job(struct JobScheduler *JS, int v_burst, int v_prioridad){
	// crea el proceso
	Proceso newJOB;
	newJOB.pid = JS->cont_PID;
	newJOB.burst = v_burst;
	newJOB.prioridad = v_prioridad;
	
	if( JS->index == JS->cant_JOB ) agrandar_cola_READY(JS);
	
	JS->READY[JS->index] = newJOB;
	JS->index += 1; //si se llena funcion para agrandar READY
	JS->cont_PID += 1;
};*/

// Funcion para enviar mensaje al cliente con el PID

// Funcion para recibir un Proceso del CPU Scheduler
/*
void reinsert_job(struct JobScheduler *JS, Proceso *job){
	if( JS->index == JS->cant_JOB ) agrandar_cola_READY();
	else{
		JS->READY[JS->index] = job;
		JS->index += 1;
	}	
}
*/

// Funcion para reagustar
/*
void reajuste_READY( struct JobScheduler *JS, v_indice int){
	int i = v_indice;
	
	while( i < JS->cant_JOB){
		JS->READY[i] = JS->READY[i+1];
	}
	JS->index -= 1;
}
*/ 

// Funcion para sacar un Proceso
/*
Proceso get_job( struct JobScheduler *JS, v_pid int){
	int i = 0;
	Proceso newJOB;
	
	while( i < JS->cant_JOB){
		if ( JS->READY[i].pid == v_pid ){
			newJOB = JS->READY[i].pid;
			reajuste_READY(JS, i);
			return newJOB;
		}
		else i++;
	}
	return newJOB; //le caeria vacio.
}
*/

int main(){
	struct JobScheduler *JS = (struct* JobScheduler) new_JobScheduler();
	int a,b;
	//insert_job(JS, 3, 4);
	
	//printf("Inserted: %d\n", (JS->READY[0]).pid );
	
	free(JS);
	return 0;
}
