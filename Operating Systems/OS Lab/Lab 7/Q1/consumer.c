#include "../headers.h"
#include "header_q1.h"
extern int isEmpty(Queue *q);
extern int dequeue(Queue *q);
void *consumer(void * param)
{
    Queue *q = (Queue *) param;
    char read_buf[MAX_NAME_LEN];
    int rollno = 0;
    while(rollno != -1)
    {
        while(isEmpty(q));
        printf("%d %s", q-> buffer[q-> front]-> rollNo, q-> buffer[q-> front]-> Name);
        rollno = dequeue(q);
        bzero(read_buf, MAX_NAME_LEN);
    }
    printf("Completed printing\n");
    pthread_exit(NULL);
}