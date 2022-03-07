#ifndef header_q1
#define header_q1

#define MAX_NAME_LEN 100
#define Q_SIZE 10
#define MAX_BUF_LEN 120
#define FILE_NAME_MAX 20

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