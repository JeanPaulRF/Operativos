#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 9999
#define SEM_KEY 1234
#define SEM_KEY2 5678

/**
void shmat(int shmid, void *shmaddr, int shmfi); 		// shmaddr se pone en 0 y el SO lo asigna
int shmdt(void *shmaddr);						// shmaddr se pone en 0 y el SO lo asigna
**/

int main(){
	while (1)
	{
		sem_wait(semB);
		// Acceder a la memoria compartida para el tipo B
		// Esperar a que no haya procesos de tipo A o C en la memoria compartida
		
		// shmat para acceder al segmento de memoria 
		// shmdt para salir de memoria al terminar
		
		key_t key = ftok("memoria_compartida", SEM_KEY2 + 1);	// generar key unica (65 id asociado al file)
		
		int shmid = shmget(key, SHM_SIZE, 0666);	// retorna id		( 1024 size de memoria , 0666 permiso para leer y escribir)
		
		char *str = (char*) shmat(shmid, (void*), 0 , 0);		// attach
		
		// ... //
		printf("Datos en memoria:  %s\n", str);
		shmdt(str);	// detach
		
		
		sem_wait(semA);
		sem_wait(semC);
		sem_post(semA);
		sem_post(semC);
		// Realizar otras tareas
		break;
		sem_post(semB);
	}
	return 0;
}
