#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_R_W 5


void * reader(void *);
void * writer(void *);


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t reader_t[NUM_R_W];
pthread_t writer_t[NUM_R_W];
int r_count = 0;
int data = 0;
int main()
{
    for (int i = 0; i < NUM_R_W; i++)
    {
        pthread_create(&reader_t[i], NULL, reader, (void *) i);
        pthread_create(&writer_t[i], NULL, writer, (void *) i);
    }

    for (int i = 0; i < NUM_R_W; i++)
    {
        pthread_join(reader_t[i], NULL);
        pthread_join(writer_t[i], NULL);
    }

    return 0;
}
void * reader(void * num)
{
    int id = (int) num;
    while(1)
    {
        pthread_mutex_lock(&mutex);
        r_count += 1;
        printf("Reader %d read data %d\n", id, data);
        r_count -= 1;
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }    
}

void * writer(void * num)
{
    int id = (int) num;
    while(1)
    {
        pthread_mutex_lock(&mutex);
        data += 1;
        printf("Writer %d read data %d \n", id, data);
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }
}