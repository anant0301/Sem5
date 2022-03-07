#include "../headers.h"
#define MAX_THREADS 10
extern void* is_prime(void *num_addr);
int main(int argc, char * argv[])
{
    int up_lim = atoi(argv[1]);
    pthread_t tid[MAX_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int arr[MAX_THREADS];
    int temp;
    for (int i = 0; i < up_lim; i++)
    {
        temp = i % MAX_THREADS;
        arr[temp] = i;
        pthread_create(&tid[temp], &attr, is_prime, &arr[temp]);
        if(temp == MAX_THREADS - 1)
        {
            for (int j = 0; j < MAX_THREADS; j++)
            {
                pthread_join(tid[j], NULL);
            }
            printf("\n");
        }
    }
    for (int j = 0; j < up_lim % MAX_THREADS; j++)
    {
        pthread_join(tid[j], NULL);
    }
    printf("\n");
    
    return 0;
}