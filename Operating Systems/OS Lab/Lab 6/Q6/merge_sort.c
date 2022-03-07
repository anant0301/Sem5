#include "../headers.h"
#include "header_q6.h"
void * merge_sort(void * param)
{
    struct q6_param * this = (struct q6_param*)param;
    
    if(this-> beg + 1== this-> len)
    {
        // printf("%d %d\n", this-> arr[this-> beg], this-> beg);
        pthread_exit(NULL);
    }
    struct q6_param * left = (struct q6_param*)malloc(sizeof(struct q6_param));
    struct q6_param * right = (struct q6_param*)malloc(sizeof(struct q6_param));
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