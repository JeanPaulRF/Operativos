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

// funciones
void printlist(node_js *head);

// crear proceso nuevo
node_js *create_new_job(int n_burst, int n_priority);

// encontrar nodo
node_js *find_node(node_js *head, int v_pid);

// retornar cabeza
node_js *get_head(node_js *head);

// insertar en la lista simple
node_js *insert_at_head(node_js **head, node_js *node_to_insert);
void insert_after_node(node_js *node_to_insert_after, node_js *newnode);
node_js *insert_at_end(node_js **head, node_js *node_to_insert);

// insertar un proceso devuelto
node_js *recibe_job(node_js **head, Proceso old_job);

// retorna un proceso y lo borra del READY
Proceso get_proceso(node_js **head, int v_pid);

// remover de la lista simple
node_js *remove_position(node_js **head, int position);
node_js *remove_last(node_js *head);
node_js *remove_first(node_js *head);

// pruebas
/*
int main(){
	// pruebas funcionalidades
	cont_PID = 1;
	cant_jobs = 0;

	READY = NULL;
	node_js *tmp;

	for(int i = 0; i<10; i++){
		tmp = create_new_job( i*2 + 5, i+1);
		insert_at_head(&READY, tmp);
	}
	printlist(READY);

	tmp = find_node(READY, 8);
	insert_after_node(tmp, create_new_job( 12 , 8));
	insert_at_end(READY, create_new_job( 77 , 11));

	tmp = get_head(READY);
	// retorno el pid recien creado
	printf("head pid: %d\n",tmp->data.pid);

	printlist(READY);

	READY = remove_first(READY);
	printf("node head remove \n");

	printlist(READY);

	READY = remove_last(READY);
	printf("node last remove \n");

	printlist(READY);

	remove_position(&READY, 4);
	printf("node in position 4 remove \n");

	printlist(READY);

	Proceso old_job;
	old_job.pid = 45;
	old_job.burst = 55;
	old_job.prioridad = 5;

	recibe_job(READY, old_job);

	printlist(READY);

	printf("Sacar un proceso, el pid = 4\n");
	old_job = get_proceso(READY, 4);
	printlist(READY);

	printf("Pid: %d\n", old_job.pid);

	return 0;
}
*/

void printlist(node_js *head)
{
	node_js *temporary = head;

	while (temporary != NULL)
	{
		printf("Pid :%d - Burst: %d - Prioridad: %d - Tiempo de Llegada: %d\n",
			   temporary->data.pid, temporary->data.burst, temporary->data.prioridad, temporary->data.tiempoLlegada);
		temporary = temporary->NEXT;
	}
	printf("\n");
}

// creo un nuevo proceso
node_js *create_new_job(int n_burst, int n_priority)
{
	node_js *result = malloc(sizeof(node_js));
	Proceso p_tmp;

	// creo el job o proceso
	p_tmp.pid = cont_PID;
	p_tmp.burst = n_burst;
	p_tmp.prioridad = n_priority;

	// ajusto las variables globales
	cont_PID++;
	cant_jobs++;

	// se inserta en el nodo job scheduler
	result->data = p_tmp;
	result->NEXT = NULL;

	return result;
}

// inserta al principio
node_js *insert_at_head(node_js **head, node_js *node_to_insert)
{
	node_to_insert->NEXT = *head;
	*head = node_to_insert;
	return node_to_insert;
}

// inserta un nodo al final
node_js *insert_at_end(node_js **head, node_js *node_to_insert)
{
	node_js *ptr = head;
	
	if(ptr == NULL){
		return node_to_insert;
	}

	while (ptr->NEXT != NULL)
		ptr = ptr->NEXT;

	ptr->NEXT = node_to_insert;
	return head;
};

// insertar despues de un nodo
void insert_after_node(node_js *node_to_insert_after, node_js *newnode)
{
	newnode->NEXT = node_to_insert_after->NEXT;
	node_to_insert_after->NEXT = newnode;
}

// encontrar un nodo
node_js *find_node(node_js *head, int v_pid)
{
	node_js *tmp = head;
	while (tmp != NULL)
	{
		if (tmp->data.pid == v_pid)
			return tmp;
		tmp = tmp->NEXT;
	}
	return NULL;
}

// regresar la cabeza
node_js *get_head(node_js *head)
{
	node_js *tmp = malloc(sizeof(node_js));
	tmp->data = head->data;
	tmp->NEXT = NULL;
	return tmp;
}

// remover el primer nodo
node_js *remove_first(node_js *head)
{
	if (head == NULL)
		printf("READY is empty\n");
	else
	{
		node_js *tmp = head;
		head = head->NEXT;
		free(tmp);
		tmp = NULL;
	}
	return head;
}

// remover el ultimo nodo
node_js *remove_last(node_js *head)
{
	if (head == NULL)
		printf("READY is empty\n");
	else if (head->NEXT == NULL)
	{
		free(head);
		head = NULL;
	}
	else
	{
		node_js *tmp = head;
		node_js *tmp2 = head;
		while (tmp->NEXT != NULL)
		{
			tmp2 = tmp;
			tmp = tmp->NEXT;
		}
		tmp2->NEXT = NULL;
		free(tmp);
		tmp = NULL;
	}
	return head;
}

// remover un una posicion especifica
node_js *remove_position(node_js **head, int position)
{
	printf("HOLLA");
	node_js *current = head;
	node_js *previous = head;
	
	
	if (*head == NULL){
		printf("READY is empty\n");
		return NULL;
	}
	else if (position == 1)
	{
		previous = current;
		current = current->NEXT;
		//free(current);
		//current = NULL;
		return previous;
	}
	else
	{
		while (position != 1)
		{
			previous = current;
			current = current->NEXT;
			position--;
		}
		previous->NEXT = current->NEXT;
		//free(current);
		current = NULL;
	}
	return head;
}

// Funcion para recibir un Proceso del CPU Scheduler
node_js *recibe_job(node_js **head, Proceso old_job)
{

	node_js *old_node = malloc(sizeof(node_js));
	node_js *ptr = head;

	old_node->data = old_job;
	old_node->NEXT = NULL;

	if( ptr != NULL){ // cuando la cabeza tiene 1 o más
		while (ptr->NEXT != NULL) ptr = ptr->NEXT;

		ptr->NEXT = old_node;
		return head;
	}
	else{ // cuando esta vacia
		ptr = old_node;
		return ptr;
	}

	
};

// Funcion para sacar un Proceso
Proceso get_proceso(node_js **head, int v_pid)
{
	node_js *tmp = head;
	Proceso p_tmp;
	int position = 1;

	p_tmp.pid = 0; // 7 digamos codigo de error

	if(tmp == NULL) {
		printf("READY is empty\n"); //no hay nada que sacar
		return p_tmp; //retornar nulo lo afectará
	}
	else{
		while (tmp != NULL) //cuando el head esta lleno
		{
			if (tmp->NEXT != NULL && tmp->NEXT->data.pid == v_pid)
			{
				
				tmp->NEXT = tmp->NEXT->NEXT;
			
				// salva la informacion del proceso buscado
				p_tmp = tmp->data;
				// borra el nodo que lo contenia
				//printf("Aqui llego %d\n", position);
				head = remove_position(head, position);
				// retorna la informacion buscada
				return p_tmp;
			}
			tmp = tmp->NEXT;
			position++;
		}

		return p_tmp;
	}
}
