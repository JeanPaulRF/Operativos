#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "algoritmosCPU.c"

#define PORT 8080
#define MAX_CLIENTS 10

int timer = 0;
int algoritmo, quantum;
int ocioso = 0;

// server
int num_clients = 0;
int server_socket, client_socket;
struct sockaddr_in server_addr;
pthread_t client_threads[MAX_CLIENTS];
int client_sockets[MAX_CLIENTS];

int running = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void menuServer();
void serverFunction();
void *handle_conections(void *arg);
void *handle_client(void *arg);
void *handle_timer();
void *handle_scheduler();
void consultas();

int main(int argc, char const *argv[])
{
    serverFunction();

    return 0;
}

void serverFunction()
{
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
    

    // hilo para Aceptar conexiones entrantes y crear hilos para manejar a los clientes

    pthread_t conections_thread;
    if (pthread_create(&conections_thread, NULL, handle_conections, NULL) != 0)
    {
        perror("Error al crear hilo de las conexiones");
        exit(-1);
    }

    consultas();

    // cerrar sockets
    for (int i = 0; i < num_clients; i++)
    {
        close(client_sockets[i]);
    }

    // Esperar a que todos los hilos terminen y cerrar sockets
    for (int i = 0; i < num_clients; i++)
    {
        pthread_join(client_threads[i], NULL);
    }
    
    printf("\n-----------FIN DE LA EJECUCION-----------\n");
    printf("\nCantidad de procesos ejecutados: \n");
    printf("\nCantidad de segundos con CPU ocioso: %d\n", ocioso);
    printf("\nTabla de TAT y WT de los procesos ejecutados: \n");
    printf("\nPromedio de Waiting Time: \n");
    printf("\nPromedio de Turn Around Time: \n\n");

/*
    printf("\n-----------READY-----------\n");
    printlist(READY);
    printf("\n\n----------EXIT------------\n");
    printlist(EXIT);
*/

    close(server_socket);

    return NULL;
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
    scanf("%d", &algoritmo);
    printf("\n\n");

    if (algoritmo == 4)
    {
        printf("Ingrese el quantum: ");
        scanf("%d", &quantum);
        printf("\n\n");
    }

    return NULL;
}

void *handle_conections(void *arg)
{
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
        // printf("Conexión entrante desde %s:%d\n\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Crear hilo para manejar al cliente
        if (pthread_create(&client_threads[num_clients], NULL, handle_client, (void *)&client_socket) != 0)
        {
            perror("Error al crear hilo");
            continue;
        }

        pthread_mutex_lock(&mutex);
        // control de sockets
        client_sockets[num_clients] = client_socket;
        num_clients++;
        pthread_mutex_unlock(&mutex);

        if (num_clients >= MAX_CLIENTS)
        {
            printf("Número máximo de clientes alcanzado\n");
            break;
        }
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
            // printf("Cliente desconectado\n");
            break; // Si el cliente se desconecta, salir del ciclo
        }
        // printf("Burst: %d del cliente %d\n", burst, client_socket);

        bytes_recv = recv(client_socket, &prioridad, sizeof(prioridad), 0); // Recibir prioridad del cliente
        if (bytes_recv <= 0)
        {
            // printf("Cliente desconectado\n");
            break; // Si el cliente se desconecta, salir del ciclo
        }
        // printf("Prioridad: %d del cliente %d\n", prioridad, client_socket);

        pthread_mutex_lock(&mutex);

        // jobScheduler -----------------------------------
        node_js *nodoTmp = malloc(sizeof(node_js));
        nodoTmp = create_new_job(burst, prioridad);
        nodoTmp->data->tiempoLlegada = timer; // Se le asigna el tiempo de llegada
        
        insert_at_end(&READY, nodoTmp);

        int pid = nodoTmp->data->pid; // Recibe el pid del proceso que se va a ejecutar

        pthread_mutex_unlock(&mutex);

        // printf("Enviando pid %d al cliente %d\n\n", pid, client_socket);
        send(client_socket, &pid, sizeof(pid), 0); // Enviar pid al cliente
    }

    close(client_socket); // Cerrar socket del cliente
    return NULL;
}

void *handle_timer(void *arg)
{
    while (1)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer++;
        pthread_mutex_unlock(&mutex);
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
                node_js *v_node;

                pthread_mutex_lock(&mutex);
                switch (algoritmo)
                {
                case 1: // si escogio FIFO
                    v_node = algoritmoFifo();
                    break;
                case 2: // si escogimos SJF
                    v_node = algoritmoSjf();
                    break;
                case 3: // si escogimos HPF
                    v_node = algoritmoHpf();
                    break;
                case 4: // si escogimos RR
                    v_node = roundRobin(quantum);
                    break;
                default: // por default que aplique el fifo
                    v_node = algoritmoFifo();
                    break;
                }
                pthread_mutex_unlock(&mutex);
                
                printf("\nProceso %d con burst %d y prioridad %d entra en ejecucion\n\n", v_node->data->pid, v_node->data->burst, v_node->data->prioridad);

                //printf("Proceso: %d Burst: %d Prioridad: %d En ejecucion\n", v_node->data->pid, v_node->data->burst, v_node->data->prioridad);

                // RR
                if (algoritmo == 4)
                {
                    if (v_node->data->burstRestante > quantum)
                    {
                        sleep(quantum);

                        v_node->data->burstRestante -= quantum;
                        
                        pthread_mutex_lock(&mutex);
                        insert_at_end(&READY, v_node);
                        pthread_mutex_unlock(&mutex);
                    }
                    else
                    {
                         sleep(v_node->data->burst);

                        v_node->data->tiempoSalida = timer - v_node->data->tiempoLlegada; // sleep suma timer + burst
                        v_node->data->tat = v_node->data->tiempoSalida - v_node->data->tiempoLlegada;
                        v_node->data->wt = v_node->data->tat - v_node->data->burst;
                        v_node->data->burstRestante = 0;
                        
                        pthread_mutex_lock(&mutex);
                        insert_at_start(&EXIT, v_node);
                        pthread_mutex_unlock(&mutex);

                        printf("\nProceso: %d terminado.\n\n", v_node->data->pid);
                    }
                }
                else
                {
                     sleep(v_node->data->burst);

		        v_node->data->tiempoSalida = timer - v_node->data->tiempoLlegada; // sleep suma timer + burst
		        v_node->data->tat = v_node->data->tiempoSalida - v_node->data->tiempoLlegada;
		        v_node->data->wt = v_node->data->tat - v_node->data->burst;
		        v_node->data->burstRestante = 0;
		        
		        pthread_mutex_lock(&mutex);
		        insert_at_start(&EXIT, v_node);
		        pthread_mutex_unlock(&mutex);

                        printf("\nProceso: %d terminado.\n\n", v_node->data->pid);
                }

                // printlist(EXIT);

            }
        }
        else{
        	sleep(1);
        	ocioso++;
        }
    }
    return NULL;
}

void consultas()
{
    int input = 99;
    printf("Opciones disponibles: \n\n");
    printf("0. Terminar la simulacion\n");
    printf("1. Ver el contenido del Ready\n\n");
    printf("Elija una opcion: ");
    scanf("%d", &input);

    if (input == 0)
    {
        return NULL;
    }
    else
    {
        pthread_mutex_lock(&mutex);
        printf("\n-----------READY-----------\n");
	    printlist(READY);
        pthread_mutex_unlock(&mutex);
        consultas();
    }
}
