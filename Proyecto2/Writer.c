#define SHM_KEY 9999
#define SEM_KEY 1234
#define SEM_KEY2 5678

while (1)
{
    sem_wait(semA);
    // Acceder a la memoria compartida para el tipo A
    sem_post(semA);
    // Realizar otras tareas
}
