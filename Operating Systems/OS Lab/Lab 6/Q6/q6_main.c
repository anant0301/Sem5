#include "../headers.h"
#include "header_q6.h"

extern void * merge_sort(void * param);
extern void * quick_sort(void * param);
int main(int argc, char * argv[])
{
    int len = argc - 1;
    int merge_arr[len];
    int quick_arr[len];
    for (int i = 0; i < len; i++)
    {
        merge_arr[i] = atoi(argv[i + 1]);
        quick_arr[i] = atoi(argv[i + 1]);
    }
    struct q6_param * merge_init = (struct q6_param*)malloc(sizeof(struct q6_param));
    merge_init-> arr = merge_arr;
    merge_init-> beg = 0;
    merge_init-> len = len;
    struct q6_param * quick_init = (struct q6_param*)malloc(sizeof(struct q6_param));
    quick_init-> arr = quick_arr;
    quick_init-> beg = 0;
    quick_init-> len = len;
    pthread_t merge;
    pthread_t quick;
    pthread_create(&merge, NULL, merge_sort, merge_init);
    pthread_create(&quick, NULL, quick_sort, quick_init);
    pthread_join(merge, NULL);
    printf("Merge Sort: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", merge_arr[i]);
    }
    printf("\n");
    printf("Quick Sort: ");
    pthread_join(quick, NULL);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", quick_arr[i]);
    }
    printf("\n");
        
    return 0;
}