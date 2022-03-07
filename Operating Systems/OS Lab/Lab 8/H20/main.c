
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

unsigned int H2O;        //how many H2O to produce
unsigned int PROD_H;      //given H
unsigned int PROD_O;      //given O

unsigned int order = 0;
unsigned int len = 0;

pthread_mutex_t mutex_hy = PTHREAD_MUTEX_INITIALIZER; //mutex on H
pthread_mutex_t mutex_oxy = PTHREAD_MUTEX_INITIALIZER;  //mutex on O
pthread_cond_t cond_hy = PTHREAD_COND_INITIALIZER; //conditional on H
pthread_cond_t cond_oxy = PTHREAD_COND_INITIALIZER;    //conditional on O

void *prod_hy(void* p)
{
    unsigned int buf = 0;
    unsigned int produced = 0;

    unsigned int seed;
    unsigned int random_wait;
    seed = time(NULL) ^ getpid() ^ pthread_self(); // just for some random output
    random_wait = rand_r(&seed) % 1000000; // random wait in micro sec, max 1 sec
;
    
    while(produced < (2 * H2O) / PROD_H)
    {
        printf("H \t start H production\n");
        //produce random wait in microsec
        usleep(random_wait);
        buf++;
        produced++;

        // add atom produced to water .. lock the on H
        pthread_mutex_lock(&mutex_hy);
        order++;
        printf("H \t thread has H %d waits for another\n", produced);
        pthread_cond_wait(&cond_hy, &mutex_hy);
        printf("H \t produce water\n");
        buf--;
        pthread_mutex_unlock(&mutex_hy);
    }
    pthread_exit(0);
}

void *prod_oxy(void* p)
{
    unsigned int buf = 0;
    unsigned int produced = 0;
    
    unsigned int seed;
    unsigned int random_wait;
    seed = time(NULL) ^ getpid() ^ pthread_self(); // just for some random output
    random_wait = rand_r(&seed) % 1000000; // random wait in micro sec, max 1 sec
    while(produced < H2O/PROD_O)
    {
        printf("O \t start producing Oxygen\n");
        //produce random wait in microsec
        usleep(random_wait);
        buf++;
        produced++;
        // add atom produced to water .. lock the on H
        pthread_mutex_lock(&mutex_oxy);
        len++;
        printf("O \t thread has produced O %d is waiting\n", produced);
        pthread_cond_wait(&cond_oxy, &mutex_oxy);
        printf("O \t produced\n");
        buf--;
        pthread_mutex_unlock(&mutex_oxy);
    }
    pthread_exit(0);
}

void *water_production(void* p)
{

    unsigned int h2o_made = 0;

    while(h2o_made < H2O)
    {
        // critical section
        pthread_mutex_lock(&mutex_hy);
        pthread_mutex_lock(&mutex_oxy);
        if(order >= 2 && len >= 1)
        {
            // wait for enough water atoms to produce water
            h2o_made++;
            order-=2;
            len--;
            printf("H2O \t number of water molecules produced %d\n\n", h2o_made);
            pthread_cond_signal(&cond_hy);
            pthread_cond_signal(&cond_hy);    //2 H taken
            pthread_cond_signal(&cond_oxy);     //1 O taken
        }
        pthread_mutex_unlock(&mutex_oxy);
        pthread_mutex_unlock(&mutex_hy);
    }
    usleep(500000);
    printf("H2O \t formed %d water molecule\n", h2o_made);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("1 arguments : [num H2O]\n");
        return 0;
    }
    H2O = atoi(argv[1]);
    PROD_H = H2O * 2;
    PROD_O = H2O;

    pthread_t hyderogen[PROD_H];
    pthread_t oxygen[PROD_O];
    pthread_t water;

    for(int i = 0; i < PROD_H; i++)
    {
        pthread_create(&hyderogen[i], NULL, prod_hy, NULL);
    }
    for(int i = 0; i < PROD_O; i++)
    {
        pthread_create(&oxygen[i], NULL, prod_oxy, NULL);
    }
    pthread_create(&water, NULL, water_production, NULL);

    for(int i = 0; i < PROD_H; i++)
    {
        pthread_join(hyderogen[i], NULL);
    }
    for(int i = 0; i < PROD_O; i++)
    {
        pthread_join(oxygen[i], NULL);
    }
    pthread_join(water, NULL);

    pthread_cond_destroy(&cond_hy);
    pthread_cond_destroy(&cond_oxy);
    return 0;
}