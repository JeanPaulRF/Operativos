#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

void *handle_client(void *arg);

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t tid;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Create a new thread to handle the client
    if (pthread_create(&tid, NULL, handle_client, (void *)&new_socket) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Liberar el pthread
    // pthread_detach(tid);

    close(server_fd);
    return 0;
}

void *handle_client(void *arg)
{

    int sock = *(int *)arg;
    int burst, prioridad, pid = 99;

    // Read incoming message from the client (burst)

    // Configurar el socket para que sea no bloqueante
    fcntl(sock, F_SETFL, O_NONBLOCK);

    // Recibir un entero del servidor
    int bytes_recv = 0;
    while (bytes_recv != sizeof(burst))
    {
        bytes_recv = recv(sock, &burst, sizeof(burst), 0);
        if (bytes_recv < 0)
        {
            // Si no hay datos disponibles, esperar un poco y volver a intentar
            usleep(1000);
        }
    }
    printf("Burst: %d\n", burst);

    // Read incoming message from the client (prioridad)

    // Configurar el socket para que sea no bloqueante
    fcntl(sock, F_SETFL, O_NONBLOCK);

    // Recibir un entero del servidor
    int bytes_recv = 0;
    while (bytes_recv != sizeof(prioridad))
    {
        bytes_recv = recv(sock, &prioridad, sizeof(prioridad), 0);
        if (bytes_recv < 0)
        {
            // Si no hay datos disponibles, esperar un poco y volver a intentar
            usleep(1000);
        }
    }
    printf("Burst: %d\n", prioridad);

    // Send response message to the client
    send(sock, &pid, sizeof(pid), 0);
    printf("Response sent\n");

    // Close the socket
    close(sock);

    return NULL;
}
