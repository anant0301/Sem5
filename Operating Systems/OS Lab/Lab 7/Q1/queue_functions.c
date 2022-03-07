#include "../headers.h"
#include "header_q1.h"

int isEmpty(Queue *q)
{
    if(q-> rear == -1) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int isFull(Queue *q)
{
    if((q-> front == -1 && q-> rear == Q_SIZE - 1) || (q-> front == (q-> rear + 1) % Q_SIZE))
    {
        return 1;
    }
    return 0;
}
void enqueue(Queue *q, const int rollno, const char *Name)
{
    if(q-> front == -1)
    {   
        q-> front = 0;
    }
    q-> rear = (q-> rear + 1) % Q_SIZE;
    Student *record = q-> buffer[q-> rear];
    sleep(0);
    strcpy(record-> Name, Name);
    record-> rollNo = rollno;
}
int dequeue(Queue *q)
{
    Student * record = q-> buffer[q->rear];
    int x = record-> rollNo;
    // printf("Inside Dequeue %d %s", record-> rollNo, record-> Name);
    if (q-> rear == q-> front)
    {
        q-> front = q-> rear = -1; 
    }
    else
    {
        q-> front = (q-> front + 1) % Q_SIZE;
    }
    return x;
}
