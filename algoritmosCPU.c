#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "jobScheduler.c"

void algoritmoFifo(node_js **headReady, node_js **headExit);
void algoritmoSjf(node_js **headReady, node_js **headExit);
int getPidShortestBurst(node_js **headReady); // pid del proceso con menos burst
void algoritmoHpf(node_js **headReady, node_js **headExit);
int getPidShortestPrioridad(node_js **headReady);
void roundRobin(node_js **headReady, node_js **headExit, int quantum);

// Algoritmo FIFO
void algoritmoFifo(node_js **headReady, node_js **headExit)
{ // pasar el ready
  Proceso procesoActual;
  node_js *tmp = headReady;
  int vpid = 0; // probar asignacion a NULL
  
  vpid = tmp->data.pid;
  procesoActual = get_proceso(headReady, vpid);
  
  if(procesoActual != NULL ) headExit = recibe_job(headExit, procesoActual);
  // else, pos no hace nada
}

// Algoritmo SJF
void algoritmoSjf(node_js **headReady, node_js **headExit)
{
  int indexShortest;
  int repeticiones = 0;
  int vpid = 0; // probar asignacion a NULL
  node_js *temporary = headReady;
  Proceso procesoActual;
  node_js *tmp = headReady;
  vpid = getPidShortestBurst(&headReady);
  procesoActual = get_proceso(headReady, vpid);
  
  if(procesoActual != NULL ) headExit = recibe_job(headExit, procesoActual);
  // else, pos no hace nada
}

int getPidShortestBurst(node_js **headReady)
{ // los procesos que ya pasaron se setean en burst = -1
  node_js *masPequenio = headReady;
  int burstTmp = INT_MAX;
  int indexShortest = INT_MAX;

  while (masPequenio != NULL)
  {
    if (masPequenio->data.burst < burstTmp)
    { // si burstRestante = 0, ya fue procesado
      indexShortest = masPequenio->data.pid;
      burstTmp = masPequenio->data.burst;
    }
    masPequenio = masPequenio->NEXT;
  }
  return indexShortest;
}

// Algoritmo HPF
void algoritmoHpf(node_js **headReady, node_js **headExit)
{
  int indexShortest;
  int repeticiones = 0;
  int vpid = 0; // probar asignacion a NULL
  node_js *temporary = headReady;
  Proceso procesoActual;
  node_js *tmp = headReady;
  vpid = getPidShortestPrioridad(&headReady);
  procesoActual = get_proceso(headReady, vpid);
  
  if(procesoActual != NULL ) headExit = recibe_job(headExit, procesoActual);
  // else, pos no hace nada
}

int getPidShortestPrioridad(node_js **headReady)
{
  node_js *masPequenio = headReady;
  int prioridadTmp = INT_MAX;
  int indexShortest = INT_MAX;

  while (masPequenio != NULL)
  {
    if (masPequenio->data.burst < prioridadTmp)
    { // si burstRestante = 0, ya fue procesado
      indexShortest = masPequenio->data.pid;
      prioridadTmp = masPequenio->data.prioridad;
    }
    masPequenio = masPequenio->NEXT;
  }
  return indexShortest;
}

// Algoritmo Round Robin
void roundRobin(node_js **headReady, node_js **headExit, int quantum)
{
  Proceso procesoActual;
  node_js *tmp = headReady;
  int vpid = 0; // probar asignacion a NULL
  vpid = tmp->data.pid;
  procesoActual = get_proceso(headReady, vpid);
  
  if(procesoActual != NULL ) headExit = recibe_job(headExit, procesoActual);
  // else, pos no hace nada
}
