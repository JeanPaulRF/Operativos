#include "proceso.h"
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define PORT 8080

char archivo[30];

void *cicloProcesos(void *arg);
void *funcionProceso(void *arg);

int main(int argc, char const *argv[])
{
    printf("\n--Bienvenido al menu de cliente manual del planificador de procesos--\n\n");
    printf("-Nombre del archivo con los procesos-\n\n");
    printf("Archivo: ");
    scanf("%s", archivo);

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    pthread_t thread;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // thread Crear procesos
    if (pthread_create(&thread, NULL, &cicloProcesos, (void *)(&sock)) != 0)
    {
        printf("\nError al crear el thread\n");
        return -1;
    }

    // Cerrar socket
    close(sock);
    return 0;
}

int getRandom(int minimo, int maximo)
{
    return rand() % (maximo - minimo + 1) + minimo;
}

void *cicloProcesos(void *arg)
{
    int sock = *(int *)arg;
    pthread_t thread;

    // while (1) segun la cantidad de procesos
    sleep(getRandom(3, 8));

    // crear thread del proceso
    pthread_create(&thread, NULL, &funcionProceso, (void *)(&sock));

    return;
}

void *funcionProceso(void *arg)
{
    int sock = *(int *)arg;

    // Crear proceso
    int burst;     // del archivo
    int prioridad; // del archivo

    // Envia datos de proceso
    send(sock, burst, sizeof(int), 0);

    send(sock, prioridad, sizeof(int), 0);

    // Recibir PCB
    recv(sock, &proceso.pid, sizeof(int), 0);
    printf("PCB recibida: %d\n", proceso.pid);

    // Solicitar CPU
    send(sock, 1, sizeof(int), 0);
    printf("PCB solicitada\n");

    // Recibir respuesta de CPU
    int respuesta;
    recv(sock, &respuesta, sizeof(int), 0);
    if (respuesta == 1)
    {
        printf("CPU recibida\n");

        // Enviar Datos de proceso
        send(sock, &proceso, sizeof(proceso), 0);
        printf("Proceso enviado\n");
    }
    else
    {
        printf("CPU no recibida\n");
    }

    return;
}