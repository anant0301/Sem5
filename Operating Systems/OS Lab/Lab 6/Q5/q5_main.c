#include "../headers.h"
#include "header_q5.h"
#include "../Q6/header_q6.h"
extern void random_fill(int arr[], int len);
extern void * merge_sort(void * param);
extern void * mean(void * param);
extern void * median(void * param);
extern void * mode (void * param);
int main(int argc, char * argv[])
{
    int len = atoi(argv[1]);
    int arr[len];
    random_fill(arr, len);
    struct q6_param * init = (struct q6_param*)malloc(sizeof(struct q6_param));
    init-> arr = arr;
    init-> beg = 0;
    init-> len = len;
    merge_sort(init);
    printf("Sorted Array: ");
    for (int i = 0; i < init-> len; i++)
    {
        printf("%d ", init-> arr[i]);
    }
    
    printf("\n");
    pthread_t tid[3];

    struct q5_param * this = (struct q5_param*)malloc(sizeof(struct q5_param));
    this-> arr = arr;
    this-> len = len;
    pthread_create(&tid[0], NULL, mean, this);
    pthread_create(&tid[1], NULL, median, this);
    pthread_create(&tid[2], NULL, mode, this);
    float *mean;
    float *median;
    int *mode;
    void * return_value;
    pthread_join(tid[0], &return_value);
    mean = (float *)return_value;
    pthread_join(tid[1], &return_value);
    median = (float *)return_value;
    pthread_join(tid[2], &return_value);
    mode = (int *)return_value;
    printf("Mean: %f\n", *mean);
    printf("Median: %f\n", *median);
    printf("Mode: %d, Frequency: %d\n", mode[0], mode[1]);
    return 0;
}