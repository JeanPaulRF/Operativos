#define SHM_KEY 9999
#define SEM_KEY 1234
#define SEM_KEY2 5678

while (1)
{
    sem_wait(semB);
    // Acceder a la memoria compartida para el tipo B
    // Esperar a que no haya procesos de tipo A o C en la memoria compartida
    sem_wait(semA);
    sem_wait(semC);
    sem_post(semA);
    sem_post(semC);
    // Realizar otras tareas
    sem_post(semB);
}
