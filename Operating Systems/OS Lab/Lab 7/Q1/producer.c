#include "../headers.h"
#include "header_q1.h"
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
        token = strtok(read_buf, ", ");
        rollno = atoi(token);
        token = strtok(NULL, ", ");
        enqueue(q, rollno, token);
        bzero(read_buf, MAX_BUF_LEN);
    }
    fclose(read_fp);
    pthread_exit(NULL);
}