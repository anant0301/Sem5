#include "../headers.h"
#include "header_q7.h"
void * random_point(void * param);
int main(int argc, char * argv[])
{
    long int radius = atoi(argv[1]);
    long int times = atoi(argv[2]);
    pthread_t tid[MAX_THREADS];
    printf("Radius: %ld, Max no of iterations: %ld\n", radius, times);
    struct q7_parameter * init = (struct q7_parameter *)malloc(sizeof(struct q7_parameter));
    init-> radius = radius;
    init-> square = radius * radius;
    init-> in_circle = init-> in_square = 0;
    int index;
    for (int i = 0; i < times; i++)
    {
        index = i % MAX_THREADS;
        pthread_create(&tid[index], NULL, random_point, init);
        if(index == MAX_THREADS - 1)
        {
            for (int j = 0; j < MAX_THREADS; j++)
            {
                pthread_join(tid[j], NULL);
            }
        }
    }
    for (int j = 0; j < times % MAX_THREADS; j++)
    {
        pthread_join(tid[j], NULL);
    }
    printf("%f\n", (double)init-> in_circle / init-> in_square * 4.00);
    return 0;
}