#include "../headers.h"
#define MAX_THREAD 3
extern int get_sum(void *num);
int main(int argc, char *argv[])
{
    int initial = atoi(argv[1]);
    int fin = atoi(argv[2]);
    int sum[MAX_THREAD];
    int num[MAX_THREAD];
    pthread_t tid[MAX_THREAD];
    int index = -1;
    for (int i = initial; i < fin; i++)
    {
        index = (index + 1) % MAX_THREAD;
        num[index] = i;
        pthread_create(&tid[index], NULL, get_sum, &num[index]);
        for(int j = 0;  index == (MAX_THREAD - 1) && j < MAX_THREAD; ++j)
        {
            pthread_join(tid[j], &sum[j]);
            if(num[j] == sum[j])
            {
                printf("%d is armstrong\n", num[j]);
            }
        }
    }
    for(int j = 0; fin % MAX_THREAD != 0 && j < fin % MAX_THREAD ; ++j)
    {
        pthread_join(tid[j], &sum[j]);
        if(num[j] == sum[j])
        {
            printf("%d is armstrong\n", num[j]);
        }
    }
    return 0;
}