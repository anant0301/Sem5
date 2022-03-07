#include <stdio.h>
#include <pthread.h>
int target_funct(void  * param);
void *target_func(void  * param);

int main()
{
    int s, p = 1;
    pthread_t tid[2];
    pthread_attr_t attr;
	pthread_attr_init(&attr);
    pthread_create(&tid[0], &attr, target_funct, NULL);
    pthread_create(&tid[1], &attr, target_func, &p);
    pthread_join(tid[0], &s);
    p = 10;
    pthread_join(tid[1], NULL);
    printf("tid_0 %d\n", s);
   
}
int target_funct(void  * param)
{
    for (int i = 0; i < 10000; ++i)
    {
        printf("%d ", 2);
    }
    printf("\n");
    return 100;
}
void *target_func(void  * param)
{
    int * k = (int *)param;
    for (int i = 0; i < 10000; ++i)
    {
        printf("%d ", *k);
    }
    printf("\n");
}