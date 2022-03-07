#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <semaphore.h>

#define DIR "/direction"
#define ROPE_SEMA "/rope_sem"
#define ROPE_LIMIT 3

void control();
void * crossover(void *);

sem_t * direction;
sem_t * rope_sem;
int b_count;
pthread_t baboon_on_rope[ROPE_LIMIT];
int main(int argc, char * argv[])
{
    b_count = atoi(argv[1]);
    if(argc == 3)
    {
        sem_unlink(DIR);
        sem_unlink(ROPE_SEMA);
    }
    
    direction = sem_open(DIR, O_CREAT, 0660, 1);
    rope_sem = sem_open(ROPE_SEMA, O_CREAT, 0660, ROPE_LIMIT);
    control();
    printf("The execution on this side is complete\n");
    return 0;
}
void control()
{
    while (b_count > 0)
    {
        sem_wait(direction);
        for (int i = 0; i < ROPE_LIMIT & b_count > 0; i++)
        {
            pthread_create(&baboon_on_rope[i], NULL, crossover, NULL);
        }
        for (int i = 0; i < ROPE_LIMIT; i++)
        {
            pthread_join(baboon_on_rope[i], NULL);
        }
        sem_post(direction);
        sleep(1);
    }

}
void * crossover(void * param)
{
    sem_wait(rope_sem);
    if(b_count <= 0) 
    {
        return NULL;
    }
    printf("%d baboons left on this side of the rope\n", --b_count);
    sleep(1);
    sem_post(rope_sem);
    pthread_exit(NULL);
}