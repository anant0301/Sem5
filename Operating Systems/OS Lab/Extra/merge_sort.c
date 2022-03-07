#ifndef headers
#define headers

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct param
{
    int *arr;
    int beg;
    int len;
};

#endif

void * merge_sort(void * param);
int main(int argc, char * argv[])
{
    int len = argc - 1;
    if (len < 1) 
    {
        printf("The arguments are\n  <executable> [array_to_be_sorted] \n");
        exit(1);
    }
    int merge_arr[len];
    for (int i = 0; i < len; i++)
    {
        merge_arr[i] = atoi(argv[i + 1]);
    }
    struct param * merge_init = (struct param*)malloc(sizeof(struct param));
    merge_init-> arr = merge_arr;
    merge_init-> beg = 0;
    merge_init-> len = len;
    pthread_t merge;
    // created this thread to make the pthread_kill function valid
    pthread_create(&merge, NULL, merge_sort, merge_init);
    pthread_join(merge, NULL);
    printf("Merge Sort: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", merge_arr[i]);
    }
    printf("\n");
    return 0;
}
void * merge_sort(void * param)
{
    struct param * this = (struct param*)param;
    
    if(this-> beg + 1== this-> len)
    {
        pthread_exit(NULL);
    }
    struct param * left = (struct param*)malloc(sizeof(struct param));
    struct param * right = (struct param*)malloc(sizeof(struct param));
    pthread_t tid_left;
    pthread_t tid_right;
    int mid;
    mid = (this-> beg + this-> len) / 2;
    left-> arr = right-> arr = this-> arr;
    left-> beg = this-> beg;
    left-> len = mid;
    right-> beg = mid;
    right-> len = this-> len;
    pthread_create(&tid_left, NULL, merge_sort, left);
    pthread_create(&tid_right, NULL, merge_sort, right);
    pthread_join(tid_left, NULL);
    pthread_join(tid_right, NULL);
    int left_index = left-> beg;
    int right_index = right-> beg;
    int index;
    int arr[this-> len - this-> beg + 1];
    for (index = 0; left_index < left-> len && right_index < right-> len; index++)
    {
        if(left-> arr[left_index] > right-> arr[right_index])
        {
            arr[index] = right-> arr[right_index++];
        }
        else
        {
            arr[index] = left-> arr[left_index++];
        }
    }
    while (left_index < left-> len)
    {
        arr[index++] = left-> arr[left_index++];
    }
    while (right_index < right-> len)
    {
        arr[index++] = right-> arr[right_index++];
    }
    index = 0;
    for (int i = this-> beg; i < this->len; i++, index++)
    {
        this-> arr[i] = arr[index];
    }
    pthread_exit(NULL);
}