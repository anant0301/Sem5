#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <stdbool.h>

#define LEFT false
#define RIGHT true 
#define ROPE_LIMIT 4
#define MAX_BABOONS 100
#define GATHER_FRUIT_TIME 1
#define baboon_sem "baboon"
#define left_sem "left"
#define right_sem "right"

typedef struct baboon{
    bool dir;
    int b_id;
    int rope_time;
} Baboon;

typedef struct node
{
    Baboon *b;
    struct node * next;
} Node;

typedef struct queue
{
    Node * front;
    Node * rear;
    int len;
} Queue;

Node * dequeue(Queue * q);
void enqueue(Queue * q, Baboon * b);
void print(Queue *q);


int l_baboon_cnt;
int r_baboon_cnt;
sem_t * baboon_rope;
sem_t * left_side; 
sem_t * right_side; 
Baboon * bbn;
pthread_attr_t attr;
pthread_t l_thread[ROPE_LIMIT];
pthread_t r_thread[ROPE_LIMIT];
Queue * right_q;
Queue * left_q;
int left_thread_id = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void * left_control(void *);
void * left_to_right(void *);
void * right_control(void *);
void * right_to_left(void * param);

int main(int argc, char * argv[])
{

    if (argc != 3)
    {
        printf("Input format ./<exec> <left_baboon_count> <right_baboon_count>\n");
        exit(1);
    }
    l_baboon_cnt = atoi(argv[1]);
    r_baboon_cnt = atoi(argv[2]);
    bbn = malloc(sizeof(Baboon) * (l_baboon_cnt + r_baboon_cnt));
    right_q = malloc(sizeof(Queue));
    left_q = malloc(sizeof(Queue));
    left_q-> len = right_q-> len = 0;
    left_q-> rear = left_q-> front = NULL;
    right_q-> rear = right_q-> front = NULL;

    pthread_t left;
    pthread_t right;
    pthread_attr_init(&attr);
    for (int i = 0; i < l_baboon_cnt; i++)
    {
        bbn[i].b_id = i;
        bbn[i].dir  = RIGHT;
        bbn[i].rope_time = rand() % ROPE_LIMIT;
        enqueue(left_q, &bbn[i]);
    }
    for (int i = left_q-> len ; i < left_q-> len + r_baboon_cnt; i++)
    {
        bbn[i].b_id = i;
        bbn[i].dir  = LEFT;
        bbn[i].rope_time = rand() % ROPE_LIMIT;
        enqueue(right_q, &bbn[i]);
    
    }
    printf("No of Baboon's are %d\n", l_baboon_cnt + r_baboon_cnt);
    // remove if any other semaphore by the names already exists
    sem_unlink(baboon_sem);
    sem_unlink(left_sem);
    sem_unlink(right_sem);
    // create semaphore for thread level synchronizatoin and read and write permission
    baboon_rope = sem_open(baboon_sem, 0, IPC_CREAT, 066, 1);
    left_side = sem_open(left_sem, 0, IPC_CREAT, 066, ROPE_LIMIT);
    right_side = sem_open(right_sem, 0, IPC_CREAT, 066, 0);

    
    pthread_create(&left, &attr, left_control, NULL);
    printf("Baboon now beginning to cross to right\n");
    pthread_create(&right, &attr, right_control, NULL);
    pthread_join(left, NULL);
    pthread_join(right, NULL);
    sem_destroy(baboon_rope);
    sem_destroy(right_side);
    sem_destroy(left_side);
    return 0;
}

void * left_control(void * param)
{
    while(true)
    {       
        sem_wait(baboon_rope);
        printf("Left to Right Crossing Begin\n");
        for (int i = 0; i < ROPE_LIMIT > l_baboon_cnt ? l_baboon_cnt:ROPE_LIMIT; i++)
        {
            pthread_create(&l_thread[i], &attr, left_to_right, NULL);
        }
        for (int i = 0; i < ROPE_LIMIT; i++)
        {
            pthread_join(l_thread[i], NULL);
        }
        sem_post(baboon_rope);
    }
}
void * left_to_right(void * param)
{   
    sem_wait(left_side);
    int i;
    sem_getvalue(left_side, &i);
    if (i <= 0) return NULL;
    pthread_mutex_lock(&mutex);
    Node * temp = dequeue(left_q);
    Baboon * b = temp-> b;
    printf("Baboon %d crossing over to right\n ", b-> b_id);
    sleep(b-> rope_time);
    printf("Baboon %d Crossed over to the right side with time %d\n ", b-> b_id, b-> rope_time);
    b-> dir = LEFT;

    print(left_q);
    pthread_mutex_unlock(&mutex);
    sem_post(right_side);
    enqueue(right_q, b);
    pthread_exit(NULL);
}


void * right_control(void * param)
{
    while(true)
    {
        sem_wait(baboon_rope);
        printf("Right to Left Crossing Begin\n");
        for (int i = 0; i < ROPE_LIMIT > r_baboon_cnt ? r_baboon_cnt:ROPE_LIMIT; i++)
        {
            pthread_create(&r_thread[i], &attr, right_to_left, NULL);
        }
        for (int i = 0; i < ROPE_LIMIT; i++)
        {
            pthread_join(r_thread[i], NULL);
        }
        sem_post(baboon_rope);
    }
}
void * right_to_left(void * param)
{
    sem_wait(right_side);
    int i;
    sem_getvalue(right_side, &i);
    if (i <= 0) return NULL;
    pthread_mutex_lock(&mutex);
    Node * temp = dequeue(right_q);
    Baboon * b = temp-> b;
    free(temp);
    printf("Baboon %d crossing over to left\n ", b-> b_id);
    sleep(b-> rope_time);
    printf("Baboon %d Crossed over to the left side with time %d\n ", b-> b_id, b-> rope_time);
    b-> dir = LEFT;
    print(right_q);
    pthread_mutex_unlock(&mutex);
    sem_post(left_side);
    enqueue(left_q, b);
    pthread_exit(NULL);
}

Node * dequeue(Queue * q)
{
    if(q-> front == NULL)
        return NULL;
    Node * temp = q-> front;
    q-> front = q-> front-> next;
    if(q-> front== NULL)
        q-> rear = NULL;
    return temp;
}

void enqueue(Queue * q, Baboon * b)
{
    Node * temp = malloc(sizeof(Node));
    temp-> b = b;
    q-> len++;
    if(q-> rear == NULL)
    {
        q-> front = q-> rear = temp;
        return ;
    }
    q-> rear-> next = temp;
    q-> rear = temp;
}

void print(Queue *q)
{
    Node * temp = q-> rear;
    int len = q-> len;
    while(len--)
    {
        printf("%d ", temp-> b-> b_id);
        temp = temp-> next;
    }
    printf("\n");
}