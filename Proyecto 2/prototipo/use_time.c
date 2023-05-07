#include <stdio.h>
#include <time.h>

int main() {
    time_t rawtime;
    struct tm *timeinfo;

    // Obtener la hora actual en segundos
    time(&rawtime);

    // Convertir la hora en una estructura tm
    timeinfo = localtime(&rawtime);

    // Acceder a los campos de la estructura tm
    int year = timeinfo->tm_year + 1900;  // Año actual
    int month = timeinfo->tm_mon + 1;     // Mes actual
    int day = timeinfo->tm_mday;          // Día del mes
    int hour = timeinfo->tm_hour;         // Hora actual
    int min = timeinfo->tm_min;           // Minuto actual
    int sec = timeinfo->tm_sec;           // Segundo actual

    // Imprimir la fecha y la hora
    printf("Fecha actual: %02d/%02d/%04d\n", day, month, year);
    printf("Hora actual: %02d:%02d:%02d\n", hour, min, sec);

    return 0;
}
