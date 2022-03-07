#ifndef header_q2
#define header_q2

#define MAX_NAME_LEN 100
#define Q_SIZE 10
#define MAX_BUF_LEN 120
#define FILE_NAME_MAX 20

// Variables for Peterson's Solution to CSP 
#define PRODUCER 0
#define CONSUMER 1
int flag[2];
int turn;

typedef struct student_record
{
    int rollNo;
    char Name[MAX_NAME_LEN];
} Student;

typedef struct queue{
    int rear;
    int front;
    struct student_record ** buffer;
} Queue;

typedef struct parameter
{
    struct queue * q;
    char * fileName;
} Parameter;

#endif