#include "../headers.h"
#include "header_q2.h"
extern int isFull(Queue *q);
extern void enqueue(Queue *q, const int rollno, const char *Name);
void *producer(void * param)
{
    printf("Reading from file: %s\n", ((Parameter *)param)-> fileName);
    Parameter *_param_ = param;
    Queue *q = _param_-> q;
    FILE *read_fp = fopen(_param_-> fileName, "r");
    char read_buf[MAX_BUF_LEN];
    char *token;
    int rollno;
    while(fgets(read_buf, MAX_BUF_LEN, read_fp))
    {

        while(isFull(q));
        // entry section
        flag[PRODUCER] = 1;
        turn = CONSUMER;
        while(turn == CONSUMER && flag[CONSUMER]);
        // critical section
        token = strtok(read_buf, ", ");
        rollno = atoi(token);
        token = strtok(NULL, ", ");
        enqueue(q, rollno, token);
        // exit section
        flag[PRODUCER] = 0;
        // remainder section
        bzero(read_buf, MAX_BUF_LEN);
    }
    fclose(read_fp);
    pthread_exit(NULL);
}