#include "proceso.h"
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

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
    if (pthread_create(&thread, NULL, cicloProcesos, (void *)&sock) < 0)
    {
        printf("\nError al crear el thread de creacion de procesos\n");
        return -1;
    }

    // Esperar a que el hilo termine(no deberia suceder)
    if (pthread_join(thread, NULL) < 0)
    {
        perror("Error al esperar el thread");
        exit(1);
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
    int sock = *(int *)arg;

    // Crear proceso
    int pid;
    int burst = getRandom(min, max);
    int prioridad = getRandom(min, max);

    // Envia datos de proceso
    if (send(sock, &burst, sizeof(burst), 0) == -1)
    {
        printf("Error al enviar el burst");
        perror("Error al enviar el burst");
        exit(EXIT_FAILURE);
    }

    if (send(sock, &prioridad, sizeof(prioridad), 0) == -1)
    {
        printf("Error al enviar la prioridad");
        perror("Error al enviar la prioridad");
        exit(EXIT_FAILURE);
    }

    // Recibir PID

    // Configurar el socket para que sea no bloqueante
    fcntl(sock, F_SETFL, O_NONBLOCK);

    // Recibir un entero del servidor
    int bytes_recv = 0;
    while (bytes_recv != sizeof(pid))
    {
        bytes_recv = recv(sock, &pid, sizeof(pid), 0);
        if (bytes_recv < 0)
        {
            // Si no hay datos disponibles, esperar un poco y volver a intentar
            usleep(1000);
        }
    }
    printf("PCB recibida: %d\n", pid);

    // Solicitar CPU
    /*
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
    */

    return NULL;
}
