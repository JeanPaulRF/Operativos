#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "jobScheduler.c"

#define PORT 8080
#define MAX_CLIENTS 10

int timer = 0;
node_js *EXIT;
int algoritmo, quantum;

void menuServer();
void serverFunction();
void *handle_client(void *arg);
void *handle_timer();
void *handle_scheduler();
void *handle_input();

int main(int argc, char const *argv[])
{
    serverFunction();

    return 0;
}

void serverFunction()
{
    struct sockaddr_in server_addr;
    int server_socket, client_socket;
    pthread_t client_threads[MAX_CLIENTS];
    int num_clients = 0;

    // variables para el scheduler
    cont_PID = 1;
    cant_jobs = 0;
    READY = NULL;
    EXIT = NULL;

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

    printf("Servidor en línea\n\n");

    menuServer();

    // Crear hilo para manejar el timer
    pthread_t timer_thread;
    if (pthread_create(&timer_thread, NULL, handle_timer, NULL) != 0)
    {
        perror("Error al crear hilo del timer");
        exit(-1);
    }

    // crear hilo del cpu-scheduler
    pthread_t scheduler_thread;
    if (pthread_create(&scheduler_thread, NULL, handle_scheduler, NULL) != 0)
    {
        perror("Error al crear hilo del scheduler");
        exit(-1);
    }

    // crear hilo para manejar input del usuario
    /*
    pthread_t input_thread;
    if (pthread_create(&input_thread, NULL, handle_input, NULL) != 0)
    {
        perror("Error al crear hilo del input");
        exit(-1);
    }
    */

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
        printf("Conexión entrante desde %s:%d\n\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

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
}

void menuServer()
{
    printf("\n--Bienvenido al servidor del planificador de procesos--\n\n");
    printf("-Algoritmos de planificacion disponibles-\n\n");
    printf("1. FIFO\n");
    printf("2. SJF\n");
    printf("3. HPF\n");
    printf("4. RR\n\n");
    printf("Elija una opcion: ");
    scanf("%d\n\n", &algoritmo);

    if (algoritmo == 4)
    {
        printf("Ingrese el quantum: ");
        scanf("%d\n\n", &quantum);
    }

    return NULL;
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

        // jobScheduler -----------------------------------
        insert_at_head(&READY, create_new_job(burst, prioridad));

        int pid = READY->data.pid; // Recibe el pid del proceso que se va a ejecutar

        READY->data.tiempoLlegada = timer; // Se le asigna el tiempo de llegada

        printf("Enviando pid %d al cliente %d\n\n", pid, client_socket);
        send(client_socket, &pid, sizeof(pid), 0); // Enviar pid al cliente
    }

    close(client_socket); // Cerrar socket del cliente

    printf("\n-----------READY-----------\n");
    printlist(READY);
    printf("\n\n----------EXIT------------\n");
    printlist(EXIT);
    return NULL;
}

void *handle_timer(void *arg)
{
    while (1)
    {
        sleep(1);
        timer++;
    }
    return NULL;
}

void *handle_scheduler(void *arg)
{
    while (1)
    {
        if (READY != NULL)
        {
            // node_js *aux = READY; no lo necesitamos, porque necesitamos ir vaciando READY
            while (READY != NULL)
            {
                //---------------
                switch (algoritmo)
                {
                case 1: // si escogio FIFO
                    algoritmoFifo(READY, EXIT);
                case 2: // si escogimos SJF
                    algoritmoSjf(READY, EXIT);
                case 3: // si escogimos HPF
                    algoritmoHpf(READY, EXIT);
                case 4: // si escogimos RR
                    roundRobin(READY, EXIT, quantum);
                default: // por default que aplique el fifo
                    algoritmoFifo(READY, EXIT);
                }

                // se obtiene el proceso
                Proceso v_proc;
                v_proc = get_proceso(EXIT, EXIT->data.pid); // tome el primer proceso, el recien enviado

                // RR
                if (algoritmo == 4)
                {
                    if (v_proc.burst > quantum)
                    {
                        sleep(quantum);

                        v_proc.burst -= quantum;
                    }
                    else
                    {
                        sleep(v_proc.burst);

                        v_proc.burstRestante = v_proc.burst;
                        v_proc.tiempoSalida = timer - v_proc.tiempoLlegada; // corregir + 7
                        v_proc.tat = v_proc.tiempoSalida - v_proc.tiempoLlegada;
                        v_proc.wt = v_proc.tat - v_proc.burstRestante;
                        v_proc.burst = 0;
                    }
                }
                else
                {
                    // ejecutar proceso
                    sleep(v_proc.burst);

                    v_proc.burstRestante = v_proc.burst;
                    v_proc.tiempoSalida = timer - v_proc.tiempoLlegada; // corregir + 7
                    v_proc.tat = v_proc.tiempoSalida - v_proc.tiempoLlegada;
                    v_proc.wt = v_proc.tat - v_proc.burstRestante;
                    v_proc.burst = 0;
                }

                if (EXIT->data.burst != 0)
                {                              // si el proceso recien enviado a exit aun tiene burts que procesar
                    recibe_job(READY, v_proc); // lo envia al final de READY
                }
            }
        }
    }
    return NULL;
}

void *handle_input(void *arg)
{
    int salir = 1;
    printf("Digite 0 para terminar la ejecucion del CPU: ");
    scanf("%d", &salir);
    if (salir == 0)
    {
        exit(0);
    }
    return NULL;
}