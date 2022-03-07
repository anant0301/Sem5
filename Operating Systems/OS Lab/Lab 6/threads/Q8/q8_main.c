#include "../headers.h"
#include "header_q8.h"
extern long long int fib_series_parallel(void * param);
int main(int argc, char *argv[])
{
    int k = 10;
    int n = atoi(argv[1]);
    int arr[k + 2];
    long long int fib_n;
    arr[0] = 0;
    arr[1] = 1;
    for(int i = 2; i <= k + 1; ++i)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    if(n > k + 1)
    {
        long long int fib_n_k;
        long long int fib_n_k_1;
        struct q8_main *t1 = (struct q8_main*)malloc(sizeof(struct q8_main)); 
        struct q8_main *t2 = (struct q8_main*)malloc(sizeof(struct q8_main)); 
        t1-> arr = t2-> arr = arr;
        t1-> k = t2-> k = k;
        t1-> n = n - k;
        t2-> n = n - k - 1;
        pthread_t tid_n_k;
        pthread_t tid_n_k_1;
        pthread_create(&tid_n_k, NULL, fib_series_parallel, t1);
        pthread_create(&tid_n_k_1, NULL, fib_series_parallel, t2);
        pthread_join(tid_n_k, &fib_n_k);
        pthread_join(tid_n_k_1, &fib_n_k_1);
        fib_n = fib_n_k * arr[k] + fib_n_k_1 * arr[k + 1];
    }
    else
    {
        fib_n = arr[n];
    }
    printf("Nth element in the fib series: %lld\n", fib_n);
    return 0;
}