#include "proceso.h"
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

#define PORT 8080

int min, max;

int getRandom(int minimo, int maximo);
void *cicloProcesos(void *arg);
void *funcionProceso(void *arg);

int main(int argc, char const *argv[])
{
    printf("\n--Bienvenido al menu de cliente automatico del planificador de procesos--\n\n");
    printf("-Rango de valores enteros para el burst y la prioridad de los procesos-\n\n");
    printf("Valor minimo: ");
    scanf("%d", &min);
    printf("Valor maximo: ");
    scanf("%d", &max);

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

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

    while (1)
    {
        pthread_t thread;

        // crear thread del proceso
        if (pthread_create(&thread, NULL, funcionProceso, (void *)&sock) < 0)
        {
            printf("\nError al crear el thread del proceso\n");
            return -1;
        }

        sleep(getRandom(2, 5));
    }

    printf("\n\n--Fin del programa--\n");

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

    while (1)
    {
        pthread_t thread;

        // crear thread del proceso
        if (pthread_create(&thread, NULL, funcionProceso, (void *)&sock) < 0)
        {
            printf("\nError al crear el thread del proceso\n");
            return NULL;
        }

        sleep(getRandom(3, 8));
    }

    return NULL;
}

void *funcionProceso(void *arg)
{
    int client_socket = *(int *)arg;
    int burst = getRandom(min, max);
    int prioridad = getRandom(min, max);

    printf("Enviando burst: %d\n", burst);
    send(client_socket, &burst, sizeof(burst), 0); // Enviar burst al servidor

    printf("Enviando prioridad: %d\n", prioridad);
    send(client_socket, &prioridad, sizeof(prioridad), 0); // Enviar burst al servidor

    // Esperar hasta que haya datos disponibles en el socket
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(client_socket, &readfds);
    int pid = select(client_socket + 1, &readfds, NULL, NULL, NULL);
    if (pid <= 0)
    {
        perror("Error en select");
        exit(EXIT_FAILURE);
    }

    recv(client_socket, &pid, sizeof(pid), 0); // Recibir pid del servidor
    printf("Recibido pid: %d\n\n", pid);

    // Solicitar CPU

    return NULL;
}
