#include <stdio.h>
#include <stdlib.h>
#include "proceso.h"

/*
	El Job Scheduler debe;
-> Recibir los mesajes del cliente { Burst(x), Prioridad(Y) } y transformarlo en un Proceso, dandole un PID.
-> Retornar un mensaje al cliente con el PID del proceso.
-> Crear una cola de READY
-> Recibir procesos sin terminar, para volver a ponerlos en la cola de READY

*/
struct node
{
	Proceso *data;
	struct node *NEXT;
};

typedef struct node node_js;

// variable global
unsigned int cont_PID;	// va asignando el id de los procesos
unsigned int cant_jobs; // va contando cuantos procesos existen
node_js *READY;			// la cola de procesos en READY

// ----------- funciones
// imprime una lista simple
void printlist(node_js *head);

// crear proceso nuevo
node_js *create_new_job(int n_burst, int n_priority);

// insertar al principio de una lista simple
void insert_at_start(node_js **head, node_js *new_node);

// insertar al final de una lista simple
void insert_at_end(node_js **head, node_js *new_node);

// buscar un proceso especifico
node_js *find_nodeJS(node_js **head, int v_pid);

// eliminar un nodo en especifico
void *delete_nodeJS(node_js **head, int v_pid);

// -------- definiciones
// imprime una lista simple
void printlist(node_js *head)
{
	node_js *temporary = head;

	while (temporary != NULL)
	{
		printf("Pid :%d - Burst: %d - Prioridad: %d - Tiempo de Llegada: %d\n",
			   temporary->data->pid, temporary->data->burst, temporary->data->prioridad, temporary->data->tiempoLlegada);
		temporary = temporary->NEXT;
	}
	printf("\n");
}

// creo un nuevo proceso
node_js *create_new_job(int n_burst, int n_priority)
{
	// reservo espacio en memoria
	
	node_js *result = malloc(sizeof(node_js));
	Proceso *v_data = malloc(sizeof(Proceso));
	
	// creo el job o proceso
	v_data->pid = cont_PID;
	
	v_data->burst = n_burst;
	v_data->prioridad = n_priority;
	v_data->tiempoLlegada = 0;
	v_data->tiempoSalida = 0;
	v_data->tat = 0;
	v_data->wt = 0;
	v_data->estado = 0;
	v_data->burstRestante = 0;
	
	// ajusto las variables globales
	cont_PID++;
	cant_jobs++;

	// se define al siguiente como nulo
	result->data = v_data;
	result->NEXT = NULL;

	return result;
}

// insertar al principio de una lista simple
void insert_at_start(node_js **head, node_js *new_node){
	// creo un puntero temporal que sirve de guia, apuntando a la lista de entrada
	node_js *temporary = head;

	// si la lista que llega esta vacia
	if(temporary == NULL) *head = new_node;
	else{ //si la lista tiene por lo menos 1 elemento
		// lo siguiente del nuevo nodo es toda la lista de entrada
		new_node->NEXT = *head;
		// la cabeza de la lista pasa a ser el nuevo nodo js
		*head = new_node;
	}
}

// insertar al final de una lista simple
void insert_at_end(node_js **head, node_js *new_node){
	// creo un puntero temporal que sirve de guia, apuntando a la lista de entrada
	node_js *temporary = head;

	// si la lista que llega esta vacia
	if(temporary == NULL){		
		//*head = new_node;
		// por alguna razon no puede, tira segmentation fault
	}
	else{ //si la lista tiene por lo menos 1 elemento
		while( temporary->NEXT != NULL ){ // mientras el siguiente no sea nulo
			temporary = temporary->NEXT; // me desplazo al siguiente
		} // al final temporary estaria en el ultimo nodo js
		temporary->NEXT = new_node;
	}
}

// buscar un proceso especifico
node_js *find_nodeJS(node_js **head, int v_pid){
	// creo un puntero temporal que sirve de guia, apuntando a la lista de entrada
	node_js *temporary = *head;

	// declaro un nodo js para almacenar el resultado
	Proceso *v_data = malloc(sizeof(Proceso));
	node_js *result = malloc(sizeof(node_js));

	// le doy valores de error por si no encuentra nada
	v_data->pid = 0;
	result->data = v_data;
	result->NEXT = NULL;

	if( temporary == NULL ){
		printf("\n List is empty \n");
		return result; // el nodo caeria con pid = 0
	} 
	else{
		if(temporary->data->pid == v_pid){ // si el primero es el buscado
			result->data = temporary->data; //copio el data y mantengo el nulo
			return result;
		}
		else{ // si hay mas de 1 elemento en la lista, busco hasta llegar al final
			while( temporary->NEXT != NULL ){ // mientras el siguiente no sea nulo, me desplazo
				if(temporary->data->pid == v_pid){
					result->data = temporary->data; //copio el data y mantengo el nulo
					return result;
				}
				temporary = temporary->NEXT; // me desplazo al siguiente
			}
			// al final solo me queda el ultimo nodo
			
			if(temporary->data->pid == v_pid){
				result->data = temporary->data; //copio el data y mantengo el nulo
				return result;
			}
			else{ // si no lo encuentro devuelve el node js con el pid = 0
				return result;
			}
		}
	}
}

// eliminar un nodo en especifico
void *delete_nodeJS(node_js **head, int v_pid){
	// creo un puntero temporal que sirve de guia, apuntando a la lista de entrada
	node_js *tmpA = *head;
	node_js *tmpB = *head;
	node_js *tmpC = *head;

	if( tmpA == NULL ){
		printf("\n List is empty \n");
	} 
	else{
		if(tmpA->data->pid == v_pid){ // si el primero es el buscado y esta solo
			if( tmpA->NEXT == NULL	){ // y esta solo
				*head = NULL; // Le asigno un nulo a la cabeza, no puedo liberar su memoria
			}
			else{ // si hay algo mas alla
				tmpA = tmpA->NEXT; // el temporal pasa al siguiente
				*head = tmpA; // la lista pasa a ser el siguiente
				free(tmpB); // libero la memoria del elemento anterior
				tmpB = NULL;				
			}
		}
		else{
			
			while( tmpA->NEXT != NULL ){ // mientras el siguiente no sea nulo, me desplazo
				if(tmpA->data->pid == v_pid){
					tmpA = tmpA->NEXT;
					free(tmpB->NEXT);
					tmpB->NEXT = NULL;
					tmpB->NEXT = tmpA;
					*head = tmpC;
					break;
				}
				tmpB = tmpA; // el previous se queda un paso por detras
				tmpA = tmpA->NEXT; // me desplazo al siguiente
				
			}
			// al final solo me queda el ultimo nodo
			
			if(tmpA->data->pid == v_pid){
				*head = tmpC;
				tmpB->NEXT = NULL;
				free(tmpA); // libero la memoria del ultimo elemento
				tmpA = NULL;
				
			}// si no lo encuentro no hace nada
		}
	}
}