#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pid;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int linea;
    char *mensaje; // Escrito por writer #999
} Mensaje;