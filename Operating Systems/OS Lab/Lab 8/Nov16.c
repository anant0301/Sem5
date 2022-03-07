#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define MAX_THREADS 5

void * reader(void *arg);
void * writer(void * arg);

sem_t mutex;
sem_t writeblock;
int data = 0;
    int rcount = 0;

int main(int argc, char * argv[])
{
    int i, b;
    pthread_t rtid[MAX_THREADS];
    pthread_t wtid[MAX_THREADS];
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);
    
    // while(1)
    // {
        for (int i = 0; i < MAX_THREADS; i++)
        {
            pthread_create(&rtid[i], NULL, reader, (void *) i);
            pthread_create(&wtid[i], NULL, writer, (void *) i);
        }
        for (int i = 0; i < MAX_THREADS; i++)
        {
            pthread_join(rtid[i], NULL);
            pthread_join(wtid[i], NULL);
        }
    // }
    return 0;
}
void * reader(void * arg)
{
    int id = (int) arg;
    sem_wait(&mutex);
    rcount += 1;
    if(rcount == 1)
        sem_wait(&writeblock);
    sem_post(&mutex);
    printf("Data read by the reader %d is %d\n", id, data);
    sleep(1);
    sem_wait(&mutex);
    rcount -= 1;
    if(rcount == 0)
        sem_post(&writeblock);
    sem_post(&mutex);       
}
void * writer(void * arg)
{
    /*get write unlock and then do the change data for showing*/
    int id = (int) arg;
    sem_wait(&writeblock);
    data++;
    printf("Data write by the writer %d is %d\n", id, data);
    sleep(1);
    sem_post(&writeblock);
}