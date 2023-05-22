#ifndef MENSAJE_H
#define MENSAJE_H

typedef struct // size = 36
{
    int pid;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int linea;
    int mensaje; // 0 vacio, 1 lleno
} Mensaje;

#endif // MENSAJE_H
