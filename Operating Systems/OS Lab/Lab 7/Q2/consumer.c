#include "../headers.h"
#include "header_q2.h"
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
        // entry section
        flag[CONSUMER] = 1;
        turn = PRODUCER;
        while(turn == PRODUCER && flag[PRODUCER]);
        // critical section
        printf("%d %s", q-> buffer[q-> front]-> rollNo, q-> buffer[q-> front]-> Name);
        rollno = dequeue(q);
        // exit section
        flag[CONSUMER] = 0;
        // remainder section
        bzero(read_buf, MAX_NAME_LEN);
    }
    printf("Completed printing\n");
    pthread_exit(NULL);
}