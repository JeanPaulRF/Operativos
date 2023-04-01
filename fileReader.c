#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar los valores
typedef struct nodo
{
    int burst;
    int prioridad;
    struct nodo *siguiente;
} Nodo;

// Con esta función agrego un valor
void agregar(Nodo **cabeza, int valor1, int valor2)
{
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->burst = valor1;
    nuevo_nodo->prioridad = valor2;
    nuevo_nodo->siguiente = NULL;
    if (*cabeza == NULL)
    {
        *cabeza = nuevo_nodo;
    }
    else
    {
        Nodo *ultimo_nodo = *cabeza;
        while (ultimo_nodo->siguiente != NULL)
        {
            ultimo_nodo = ultimo_nodo->siguiente;
        }
        ultimo_nodo->siguiente = nuevo_nodo;
    }
}

Nodo *getFileList()
{
    // Abrir archivo
    FILE *archivo = fopen("archivo.txt", "r");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    Nodo *lista_procesos = NULL;

    char linea[100];
    fgets(linea, 100, archivo);
    char *burst = "Burst";
    char *prioridad = "Prioridad";

    // Agregar los datos
    int valor_burst, valor_prioridad;
    while (fscanf(archivo, "%d\t%d", &valor_burst, &valor_prioridad) == 2)
    {
        agregar(&lista_procesos, valor_burst, valor_prioridad);
        
    }

    fclose(archivo);

    // Imprimir las listas
    printf("Lista %s:\n", burst);
    Nodo *nodo_burst = lista_procesos;
    Nodo *nodo_prioridad = lista_procesos;
    while (nodo_burst != NULL)
    {
        printf("%d\n", nodo_burst->burst);
        nodo_burst = nodo_burst->siguiente;
    }
    printf("\nLista %s:\n", prioridad);
    while (nodo_prioridad != NULL)
    {
        printf("%d\n", nodo_prioridad->prioridad);
        nodo_prioridad = nodo_prioridad->siguiente;
    }

    return lista_procesos;
}