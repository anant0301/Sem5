#include "../headers.h"
#include "header_q2.h"

extern void *consumer(void * param);
extern void *producer(void * param);
int main(int argc, char * argv[])
{
    char *readFile = malloc(sizeof(char) * FILE_NAME_MAX);
    readFile = argv[1];
    Student *buffer[Q_SIZE]; 
    for (int i = 0; i < Q_SIZE; ++i)
    {
        buffer[i] = (Student *)malloc(sizeof(Student) * Q_SIZE);
    }
    Queue *q = malloc(sizeof(Queue));
    Parameter *param = malloc(sizeof(Parameter));
    q-> buffer = buffer;
    q-> rear = -1;
    q-> front = -1;
    param-> q = q;
    param-> fileName =  readFile;
    pthread_t pthr, cthr;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&pthr, &attr, producer, param);
    pthread_create(&cthr, &attr, consumer, q);
    printf("Thread Creation Complete\n");
    pthread_join(pthr, NULL);
    pthread_join(cthr, NULL);
    printf("Thread Execution Complete\n");
    return 0;
}