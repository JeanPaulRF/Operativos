#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define MAX_CLIENTS 10

void *handle_client(void *arg);

int main(int argc, char const *argv[])
{
    struct sockaddr_in server_addr;
    int server_socket, client_socket;
    pthread_t client_threads[MAX_CLIENTS];
    int num_clients = 0;

    // Crear socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Asociar socket con dirección del servidor
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Error al asociar socket con dirección del servidor");
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_socket, MAX_CLIENTS) < 0)
    {
        perror("Error al escuchar conexiones entrantes");
        exit(EXIT_FAILURE);
    }

    printf("Servidor en línea\n");

    // Aceptar conexiones entrantes y crear hilos para manejar a los clientes
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0)
        {
            perror("Error al aceptar conexión entrante");
            continue;
        }
        printf("Conexión entrante desde %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Crear hilo para manejar al cliente
        if (pthread_create(&client_threads[num_clients], NULL, handle_client, (void *)&client_socket) != 0)
        {
            perror("Error al crear hilo");
            continue;
        }
        num_clients++;
        if (num_clients >= MAX_CLIENTS)
        {
            printf("Número máximo de clientes alcanzado\n");
            break;
        }
    }

    // Esperar a que todos los hilos terminen y cerrar sockets
    for (int i = 0; i < num_clients; i++)
    {
        pthread_join(client_threads[i], NULL);
    }
    close(server_socket);
    return 0;
}

void *handle_client(void *arg)
{
    int client_socket = *(int *)arg;

    while (1)
    {
        int burst, prioridad;
        int bytes_recv = recv(client_socket, &burst, sizeof(burst), 0); // Recibir burst del cliente
        if (bytes_recv <= 0)
        {
            printf("Cliente desconectado\n");
            break; // Si el cliente se desconecta, salir del ciclo
        }
        printf("Burst: %d del cliente %d\n", burst, client_socket);

        bytes_recv = recv(client_socket, &prioridad, sizeof(prioridad), 0); // Recibir prioridad del cliente
        if (bytes_recv <= 0)
        {
            printf("Cliente desconectado\n");
            break; // Si el cliente se desconecta, salir del ciclo
        }
        printf("Prioridad: %d del cliente %d\n", prioridad, client_socket);

        int pid = 99; // Generar número aleatorio
        printf("Enviando pid %d al cliente %d\n", pid, client_socket);
        send(client_socket, &pid, sizeof(pid), 0); // Enviar pid al cliente
    }

    close(client_socket); // Cerrar socket del cliente
    return NULL;
}
