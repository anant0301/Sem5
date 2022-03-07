#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 1
#define N 5
#define LEFT (ph_num + 1) % N
#define RIGHT (ph_num + 4) % N

//  2 semaphores
// mutex -- binary sem... here it is like the checker to resource allocations
sem_t mutex;// overall synchronization across philosophers... provides the fair chance for other threads to use the resource 
sem_t S[N]; // the adjacent philosphers are not eating... this is only for this code

void * philosopher(void *num); // runner in thread 
void take_fork(int);
void put_fork(int);
void test(int);
int state[N]; // flag in peterson's... desire to enter critical section
int phil_num[N] = {0, 1, 2, 3, 4};
int main(int argc, char *argv[])
{
    int i;
    pthread_t thread_id[N];
    // let the sem be shared... (, 0, ) --- shared or non-shared across threads--- 0--> shared across threads
    sem_init(&mutex, 0, 1); // (,, 1) -- initial start variable
    for ( i = 0; i < N; i++)
    {
        sem_init(&S[i], 0, 0);
    }
    for ( i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &phil_num[i]);
        printf("Philosopher %d is ret \n", i + 1);
    }
    for ( i = 0; i < N; i++)
    {
        pthread_join(thread_id[i], NULL);
    }    
    return 0;
}
void * philosopher(void *num)// runner in thread 
{
    while(1)
    {
        // sleep are used to ensuring the locking functions are working properly
        int * i = num;
        sleep(1); 
        take_fork(*i); // it is taking 2 forks 
        sleep(0);
        put_fork(*i);
    }
    pthread_exit(NULL);
}
void take_fork(int ph_num)
{
    // state[ph_num] = HUNGRY; /// try this 
    sem_wait(&mutex);  // gain the lock over mutex --- mutex becomes 0 from 1
    state[ph_num] = HUNGRY;
    printf("Philospher %d is hungry\n", ph_num + 1);
    test(ph_num); // test whether the thread can move to the eating state
    sem_post(&mutex); // release ... to not hold the outer synchronization of threads
    sem_wait(&S[ph_num]); // test will make 0-->1 here it comes bakc to 1-->0
    sleep(1);   // test if sombody else is allowed to take control
}
void test(int ph_num)
{
    if(state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[ph_num] = EATING;
        sleep(2);
        printf("Philosopher %d takes the fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);
        printf("Philosopher %d is eating\n", ph_num + 1);
        sem_post(&S[ph_num]); // release the lock
    }
}
void put_fork(int ph_num)
{
    // mutex lock in the take fork 
// it is as the every other thread would release lock in the take_fork -- means the post of mutex is allowed to happen (it can wait till it gets the lock)
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("Philosopher %d releases the fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}