#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar los valores
typedef struct nodo
{
    int valor;
    struct nodo *siguiente;
} Nodo;

// Con esta función agrego un valor
void agregar(Nodo **cabeza, int valor)
{
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->valor = valor;
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

int main()
{
    // Abrir archivo
    FILE *archivo = fopen("archivo.txt", "r");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    Nodo *lista_burst = NULL;
    Nodo *lista_prioridad = NULL;

    char linea[100];
    fgets(linea, 100, archivo);
    char *burst = "Burst";
    char *prioridad = "Prioridad";

    // Agregar los datos
    int valor_burst, valor_prioridad;
    while (fscanf(archivo, "%d\t%d", &valor_burst, &valor_prioridad) == 2)
    {
        agregar(&lista_burst, valor_burst);
        agregar(&lista_prioridad, valor_prioridad);
    }

    fclose(archivo);

    // Imprimir las listas
    printf("Lista %s:\n", burst);
    Nodo *nodo_burst = lista_burst;
    while (nodo_burst != NULL)
    {
        printf("%d\n", nodo_burst->valor);
        nodo_burst = nodo_burst->siguiente;
    }
    printf("\nLista %s:\n", prioridad);
    Nodo *nodo_prioridad = lista_prioridad;
    while (nodo_prioridad != NULL)
    {
        printf("%d\n", nodo_prioridad->valor);
        nodo_prioridad = nodo_prioridad->siguiente;
    }

    return 0;
}