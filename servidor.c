#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error! No se ingreso el puerto por parametro\n");
    }
    else
    {
        // Definir variables
        int fd, fd2, longitud_cliente, puerto;
        puerto = atoi(argv[1]);

        // Se necesitan dos estructuras de tipo sockaddr_in
        // Una para el servidor y otra para el cliente
        struct sockaddr_in servidor, cliente;

        // Configurar la estructura del servidor
        servidor.sin_family = AF_INET;         // Familia de direcciones TCP/IP
        servidor.sin_port = htons(puerto);     // Puerto
        servidor.sin_addr.s_addr = INADDR_ANY; // Cualquier direccion IP
        bzero(&(servidor.sin_zero), 8);        // Rellenar con ceros el resto de la estructura

        // Definir el socket
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("Error al abrir el socket\n");
            exit(-1);
        }

        // Asociar el socket a una direccion IP y puerto
        if (bind(fd, (struct sockaddr *)&servidor, sizeof(struct sockaddr)) == -1)
        {
            printf("Error al asociar el socket a la direccion IP y puerto\n");
            exit(-1);
        }

        // Poner al socket en modo escucha
        if (listen(fd, 5) == -1)
        {
            printf("Error al poner al socket en modo escucha\n");
            exit(-1);
        }

        // Aceptar conexiones
        while (1)
        {
            longitud_cliente = sizeof(struct sockaddr_in);
            if ((fd2 = accept(fd, (struct sockaddr *)&cliente, &longitud_cliente)) == -1)
            {
                printf("Error al aceptar conexiones\n");
                exit(-1);
            }
            printf("Se obtuvo una conexion desde %s\n", inet_ntoa(cliente.sin_addr));
            // Enviar y recibir datos
            send(fd2, "Hola Cliente\n", 13, 0);
            close(fd2);
        }
    }

    return 0;
}