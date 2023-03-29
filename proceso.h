#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int pid;
    int burst;
    int prioridad;
    int tiempoLlegada;
    int tiempoSalida;
    int tat;
    int wt;
    int estado; // 0: listo, 1: ejecutando, 2: terminado
    int burstRestante;
} Proceso;
