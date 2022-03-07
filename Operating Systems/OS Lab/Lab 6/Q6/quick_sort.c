#include "../headers.h"
#include "header_q6.h"

void * quick_sort(void * param)
{
    struct q6_param * this = (struct q6_param*)param;
    if(this-> len - 1 < this-> beg)
    {
        pthread_exit(NULL);
    }
    int *arr = this-> arr;
    int len = this-> len - 1;
    int beg = this-> beg;
    int pivot = len;
    int right_ptr = len - 1;
    int left_ptr = this-> beg;
    while(left_ptr < right_ptr && left_ptr < pivot && right_ptr > beg)
    {
        while(arr[left_ptr] < arr[pivot] && left_ptr < pivot && right_ptr > beg)
        {
            left_ptr++;
        }
        while(arr[right_ptr] > arr[pivot] && left_ptr < pivot && right_ptr > beg)
        {
            right_ptr--;
        }
        if(right_ptr > left_ptr)
        {
            arr[right_ptr] = arr[right_ptr] ^ arr[left_ptr]; 
            arr[left_ptr] = arr[right_ptr] ^ arr[left_ptr]; 
            arr[right_ptr] = arr[right_ptr] ^ arr[left_ptr]; 
            left_ptr++;
        }
        
    }
    if(pivot > left_ptr && arr[pivot] < arr[left_ptr])
    {
        arr[pivot] = arr[pivot] ^ arr[left_ptr]; 
        arr[left_ptr] = arr[pivot] ^ arr[left_ptr]; 
        arr[pivot] = arr[pivot] ^ arr[left_ptr];
    }
    pthread_t tid_left;    
    pthread_t tid_right;
    struct q6_param* left = calloc(1, sizeof(struct q6_param));
    struct q6_param* right = calloc(1, sizeof(struct q6_param));
    left-> arr = right-> arr = arr;
    left-> beg = this-> beg;
    left-> len = left_ptr;
    right-> beg = left_ptr + 1;
    right-> len = this-> len;
    if(right-> beg < this-> len)
    {
        pthread_create(&tid_left, NULL, quick_sort, right);
    }
    if(left-> len > this-> beg)
    {
        pthread_create(&tid_left, NULL, quick_sort, left);
    }
    pthread_join(tid_right, NULL);
    pthread_join(tid_left, NULL);
    pthread_exit(NULL);
}