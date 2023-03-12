#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("Error! No se ingreso el puerto por parametro\n");
    }
    else
    {
        // Definir variables
        char *ip;
        int fd, puerto, numbytes;
        char buf[100];
        puerto = atoi(argv[2]);
        ip = argv[1];

        struct hostent *he;
        // Estrucutra que contiene informacion sobre un host en internet
        struct sockaddr_in servidor;
        // Estructura que contiene la direccion del servidor

        if ((he = gethostbyname(ip)) == NULL)
        {
            // gethostbyname() devuelve informacion sobre el host cuyo nombre es
            // pasado como parametro. La estructura hostent es definida en el archivo
            // netdb.h
            printf("Error al obtener informacion del host\n");
            exit(-1);
        }

        // Definir el socket
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            printf("Error al abrir el socket\n");
            exit(-1);
        }

        // Datos del servidor
        servidor.sin_family = AF_INET;     // Familia de direcciones TCP/IP
        servidor.sin_port = htons(puerto); // Puerto
        servidor.sin_addr = *((struct in_addr *)he->h_addr);
        // La funcion inet_addr() convierte una direccion IP en formato
        bzero(&(servidor.sin_zero), 8); // Rellenar con ceros el resto de la estructura

        // Conectar al servidor
        if (connect(fd, (struct sockaddr *)&servidor, sizeof(struct sockaddr)) == -1)
        {
            printf("Error al conectar al servidor\n");
            exit(-1);
        }

        if ((numbytes = recv(fd, buf, 100, 0)) == -1)
        {
            printf("Error al recibir datos del servidor\n");
            exit(-1);
        }

        buf[numbytes] = '\0';

        printf("Mensaje del servidor: %s\n", buf);
        // Muestra el mensaje del servidor

        close(fd);
    }
    return 0;
}