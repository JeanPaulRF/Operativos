#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de un nodo de la lista
typedef struct nodo {
    int valor;
    struct nodo* siguiente;
} Nodo;

// Función para agregar un valor a la lista
void agregar(Nodo** cabeza, int valor) {
    Nodo* nuevo_nodo = (Nodo*) malloc(sizeof(Nodo));
    nuevo_nodo->valor = valor;
    nuevo_nodo->siguiente = NULL;
    if (*cabeza == NULL) {
        *cabeza = nuevo_nodo;
    } else {
        Nodo* ultimo_nodo = *cabeza;
        while (ultimo_nodo->siguiente != NULL) {
            ultimo_nodo = ultimo_nodo->siguiente;
        }
        ultimo_nodo->siguiente = nuevo_nodo;
    }
}

int main() {
    // Abrir el archivo de texto
    FILE* archivo = fopen("archivo.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    // Inicializar las listas para almacenar los datos
    Nodo* lista_burst = NULL;
    Nodo* lista_prioridad = NULL;

    // Leer cada línea del archivo
    int burst, prioridad;
    while (fscanf(archivo, "%d %d", &burst, &prioridad) == 2) {
        // Agregar los datos a las respectivas listas
        agregar(&lista_burst, burst);
        agregar(&lista_prioridad, prioridad);
    }

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los datos de las listas
    printf("Lista Burst:\n");
    Nodo* nodo_burst = lista_burst;
    while (nodo_burst != NULL) {
        printf("%d\n", nodo_burst->valor);
        nodo_burst = nodo_burst->siguiente;
    }
    printf("\nLista Prioridad:\n");
    Nodo* nodo_prioridad = lista_prioridad;
    while (nodo_prioridad != NULL) {
        printf("%d\n", nodo_prioridad->valor);
        nodo_prioridad = nodo_prioridad->siguiente;
    }

    // Liberar la memoria de las listas
    Nodo* nodo_actual = lista_burst;
    Nodo* nodo_siguiente;
    while (nodo_actual != NULL) {
        nodo_siguiente = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual = nodo_siguiente;
    }
    nodo_actual = lista_prioridad;
    while (nodo_actual != NULL) {
        nodo_siguiente = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual = nodo_siguiente;
    }

    return 0;
}