#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "Inicializador.c"

#define SHM_KEY 9999
#define SEM_KEY 1234
#define SEM_KEY2 5678

/**
void shmat(int shmid, void *shmaddr, int shmfi); 		// shmaddr se pone en 0 y el SO lo asigna
int shmdt(void *shmaddr);						// shmaddr se pone en 0 y el SO lo asigna


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


/**
**
**/ 

// semget(key_t key, int nsems, int semflg);
// semop(int semid, struct sembuf *sops, size_t nsops);

void reader(int lector_id, int tiempo_lectura, int tiempo_dormir){
		// obtener el identificador de la memoria compartida
    int shm_id = shmget(SHM_KEY, SIZE_LINEA, 0666);		// SIZE_LINEA -> era SHARED_MEMORY_SIZE
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // adjuntar el segmento de memoria compartida
    char *shm_addr = shmat(shm_id, NULL, 0);
    if (shm_addr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // obtener el identificador del conjunto de semáforos
    int sem_id = semget(SEM_KEY2, 1, 0);		// primer parámetro SEMAPHORE_KEY
    if (sem_id == -1) {
        perror("semget");
        exit(1);
    }
		// lecturas de memoria
		while(1) {
			// bloqueo del semáforo
			struct sembuf sem_lock = {0, -1, 0};		// {id del semaforo, bloqueo- o desbloqueo+, flag para comportamiento normal }
			if (semop(sem_id, &sem_lock, 1) == -1) {
					perror("semop");
					exit(1);
			}

			// leer todo el mensaje en memoria
			//printf("Mensaje recibido: %s\n", shm_addr);

			// lectura de una línea de memoria
      printf("Lector %d leyendo: %s\n", lector_id, shm_addr);

      // desbloqueo del semáforo
      struct sembuf sem_unlock = {0, 1, 0};
      if (semop(sem_id, &sem_unlock, 1) == -1) {
          perror("semop");
          exit(1);
      }

      // sleep deseado
      sleep(tiempo_lectura);

      // moverse a la siguiente linea de memoria para leerla
      shm_addr += strlen(shm_addr) + 1;

      // verificación de final de memoria para volver al inicio
      if (shm_addr >= shm_addr + SIZE_LINEA) {
          // Reiniciar al comienzo de la memoria compartida
          shm_addr = shmat(shm_id, NULL, 0);
      }

      // sleep deseado
      sleep(tiempo_dormir);
    }

    // detach (aqui o en main?)
    shmdt(shm_addr);
}