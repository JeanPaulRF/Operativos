#include <stdio.h>
#include <stdlib.h>
#include "proceso.h"
#include "jobScheduler.c"

void algoritmoFifo(Proceso cola[]);
void cargarAJobScheduler(Proceso procesoActual);
void algoritmoSjf(Proceso cola[]);
int getIndexShortest(Proceso cola[]); //indice del proceso con menos burst
void algoritmoHpf(Proceso cola[]);
int getIndexPrioridad(Proceso cola[]);
void roundRobin(Proceso cola[], int quantum);

// Algoritmo FIFO
void algoritmoFifo(Proceso cola[]){
  Proceso procesoActual;
  for (int i = 0; cola.size; i++) {   // llevar registro del tamaño de la cola
    procesoActual = cola[i];
    cargarAJobScheduler(procesoActual);
  }
}

// Algoritmo SJF
void algoritmoSjf(struct Proceso cola[]) {
  int indexShortest;
  int repeticiones = 0;
  while(repeticiones < cola.size) {   // borrar procesos terminados?
    indexShortest = getIndexShortest(cola);
    cargarAJobScheduler(cola[indexShortest]);
    cola[indexShortest].burstRestante = 0;  //setear el burst como ya procesado
    repeticiones ++;
  }
}

int getIndexShortest(Proceso cola[]) { // los procesos que ya pasaron se setean en burst = -1
  Proceso masPequenio = cola[0];
  int indexShortest;
  
  for(int i = 1 ; i < cola.size - 1 ; i++) {
    if((cola[i].burst < masPequenio.burst) && (cola[i].burstRestante > 0)) { //si burstRestante = 0, ya fue procesado
      masPequenio = cola[i];
      indexShortest = i;
    }
  }
  return indexShortest;
}

// Algoritmo HPF
void algoritmoHpf(Proceso cola[]) {
  cargarAJobScheduler(cola[0]); // se carga el proceso1
  int repeticiones = 1;
  int indexPrioridad;

  while(repeticiones < cola.size) {
    indexPrioridad = getIndexPrioridad(cola);
    cargarAJobScheduler(cola[indexPrioridad]);
  }
}

int getIndexPrioridad(Proceso cola[]) {
  int indexPrioridadMayor = 1;    // empieza en 1 porque el proceso1 siempre ejecuta primero
  for (int i = 2 ; i < cola.size; i++) {  
    if(cola[i].prioridad > cola[indexPrioridadMayor].prioridad) {
      indexPrioridadMayor = i;
    } else if(cola[i].prioridad == cola[indexPrioridadMayor].prioridad) {
      indexPrioridadMayor = (cola[i].pid < cola[indexPrioridadMayor].pid) ? i : indexPrioridadMayor; // si tienen igual prioridad retorna pid mas bajo
    }
  }
  return indexPrioridadMayor;
}


// Algoritmo Round Robin
void roundRobin(Proceso cola[], int quantum){
  int cantProcesosTerminados = 0;
  int indexActual = 0;
  while(cantProcesosTerminados != cola.size) {
    if(cola[indexActual].burstRestante > quantum) {
      cola[indexActual].burstRestante = cola[indexActual].burstRestante - quantum;
    } else {
      cola[indexActual].burstRestante = 0;
      cantProcesosTerminados ++;
    }
    indexActual ++;
  }
}

void cargarAJobScheduler(Proceso procesoActual) {
  jobScheduler.add(procesoActual);
}

