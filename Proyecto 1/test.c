#include <stdio.h>
#include <stdlib.h>
#include "jobScheduler.c"

int main(){
	// pruebas funcionalidades
	cont_PID = 1;
	cant_jobs = 0;
	no_pruebas = 0;
	
	READY = NULL;
	node_js *tmp;
	
	tmp = create_new_job(7, 4);
	insert_at_end(&READY, tmp);
	printlist(READY);
	
	tmp = create_new_job(8, 2);
	insert_at_start(&READY, tmp);
	printlist(READY);
	
	tmp = create_new_job(6, 2);
	insert_at_start(&READY, tmp);
	printlist(READY);
	
	tmp = create_new_job(8, 4);
	insert_at_start(&READY, tmp);
	printlist(READY);
	
	tmp = create_new_job(7, 4);
	insert_at_end(&READY, tmp);
	printlist(READY);
	
	tmp = create_new_job(9, 1);
	insert_at_end(&READY, tmp);
	printlist(READY);
	
	register_result(READY, "results.txt");
	int r = number_of_nodes(READY);
	
	printf("\n Numero de nodos = %d \n", r);
	
	tmp = find_nodeJS(&READY, 3);
	printlist(tmp);
	printlist(READY);
	
	delete_nodeJS(&READY, 3);
	printlist(READY);
	
	delete_nodeJS(&READY, 5);
	printlist(READY);
	
	delete_nodeJS(&READY, 1);
	printlist(READY);
	
	delete_nodeJS(&READY, 2);
	printlist(READY);
	
	delete_nodeJS(&READY, 4);
	printlist(READY);
}