#include <stdio.h>
#include <stdlib.h>
#include "proceso.c"
#include "jobScheduler.c"

void algoritmoFifo(struct Proceso cola[]);
void cargarAJobScheduler(struct Proceso procesoActual);
void algoritmoSjf(struct Proceso cola[]);
int getIndexShortest(struct Proceso cola[]); //indice del proceso con menos burst
void algoritmoHpf(struct Proceso cola[]);
int getIndexPrioridad(struct Proceso cola[]);

// Algoritmo FIFO
void algoritmoFifo(struct Proceso cola[]){
  struct Proceso procesoActual;
  for (int i = 0; cola.size; i++) {   // llevar registro del tamaño de la cola
    procesoActual = cola[i];
    cargarAJobScheduler(procesoActual);
  }
}

// Algoritmo SJF
void algoritmoSjf(struct Proceso cola[]) {
  int indexShortest;
  int repeticiones = 0;
  while(repeticiones < cola.size) {
    indexShortest = getMasPequenio(cola);
    cargarAJobScheduler(cola[indexShortest]);
    cola[indexShortest].burst = -1;  //setear el burst como ya procesado
    repeticiones ++;
  }
}

int getIndexShortest(struct Proceso cola[]) { // los procesos que ya pasaron se setean en burst = -1
  struct Proceso masPequenio = cola[0];
  int indexShortest;
  
  for(int i = 1 ; i < cola.size - 1 ; i++) {
    if((cola[i].burst < masPequenio.burst) && (cola[i].burst > 0)) {
      masPequenio = cola[i];
      indexShortest = i;
    }
  }
  return indexShortest;
}

// Algoritmo HPF
void algoritmoHpf(struct Proceso cola[]) {
  cargarAJobScheduler(cola[0]); // se carga el proceso1
  int repeticiones = 1;
  int indexPrioridad;

  while(repeticiones < cola.size) {
    cargarAJobScheduler(cola[indexPrioridad]);
  }
}

int getIndexPrioridad(struct Proceso cola[]) {
  int indexPrioridadMayor = 1;
  for (int i = 2 ; i < cola.size; i++) {  // empieza en 1 porque el proceso1 siempre ejecuta primero
    if(cola[i].prioridad > cola[indexPrioridadMayor].prioridad) {
      indexPrioridadMayor = i;
    }
  }
  return indexPrioridadMayor;
}

void roundRobin(struct Proceso cola[]){

}

void cargarAJobScheduler(struct Proceso procesoActual) {
  jobScheduler.add(procesoActual);
}

