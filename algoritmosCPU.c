#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "jobScheduler.c"

void algoritmoFifo();
void algoritmoSjf();
int getPidShortestBurst(); // pid del proceso con menos burst
void algoritmoHpf();
int getPidShortestPrioridad();
void roundRobin(int quantum);

// Algoritmo FIFO
void algoritmoFifo()
{ 
// pasar el ready
  node_js *nodeActual;
  node_js *tmp = READY;
  int vpid = 0; // probar asignacion a NULL
  
  vpid = tmp->data->pid;
  nodeActual = find_nodeJS(&READY, vpid); //deberia ser el head

  if(nodeActual->data->pid != 0){
    delete_nodeJS(&READY, nodeActual);
  	insert_at_start(&EXIT, nodeActual);
  }

}

// Algoritmo SJF
void algoritmoSjf()
{
  int vpid = 0; // probar asignacion a NULL
  node_js *nodeActual;
  vpid = getPidShortestBurst();
  nodeActual = find_nodeJS(&READY, vpid);  
  
  if(nodeActual->data->pid != 0) 
  {
    delete_nodeJS(&READY, nodeActual);
    insert_at_start(&EXIT, nodeActual);
  } 
  // else, pos no hace nada
}

int getPidShortestBurst()
{ 
  node_js *masPequenio = READY; // puede que deba corregirse READY a &READY
  int burstTmp = INT_MAX;
  int indexShortest = INT_MAX;

  while (masPequenio != NULL)
  {
    if (masPequenio->data->burst < burstTmp)
    { // si burstRestante = 0, ya fue procesado
      indexShortest = masPequenio->data->pid;
      burstTmp = masPequenio->data->burst;
    }
    masPequenio = masPequenio->NEXT;
  }
  return indexShortest;
}

// Algoritmo HPF
void algoritmoHpf()
{
  //int indexShortest;
  //int repeticiones = 0;
  int vpid = 0; // probar asignacion a NULL
  //node_js *temporary = headReady;
  node_js *nodeActual;
  //node_js *tmp = headReady;
  vpid = getPidShortestPrioridad();
  nodeActual = find_nodeJS(&READY, vpid);
  
  if(nodeActual->data->pid != 0)
  {
    delete_nodeJS(&READY, nodeActual);
    insert_at_start(&EXIT, nodeActual);
  }
  // else, pos no hace nada
}

int getPidShortestPrioridad()
{
  node_js *masPequenio = READY;   // puede que deba corregirse READY a &READY
  int prioridadTmp = INT_MAX;
  int indexShortest = INT_MAX;

  while (masPequenio != NULL)
  {
    if (masPequenio->data->burst < prioridadTmp)
    { // si burstRestante = 0, ya fue procesado
      indexShortest = masPequenio->data->pid;
      prioridadTmp = masPequenio->data->prioridad;
    }
    masPequenio = masPequenio->NEXT;
  }
  return indexShortest;
}

// Algoritmo Round Robin
void roundRobin(int quantum)
{
  node_js *nodeActual;
  node_js *tmp = READY;  // puede que deba corregirse READY a &READY
  int vpid = 0; // probar asignacion a NULL
  vpid = tmp->data->pid;
  nodeActual = find_nodeJS(&READY, vpid);  //get_proceso(headReady, vpid);
  
  if(nodeActual->data->pid != 0)
  {
    delete_nodeJS(&READY, nodeActual);
    insert_at_start(&EXIT, nodeActual);
  }
  // else, pos no hace nada
}
