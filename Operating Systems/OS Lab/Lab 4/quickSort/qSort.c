#include "headers.h"

int qSort(int arr[], int right, int left, int pivot)
{
    int left_ptr = left;
    int right_ptr = right - 1;
    while(1)
    {
        while(arr[++left_ptr] < pivot);
        while(right_ptr > 0 && arr[--right_ptr] < pivot);
        if(left_ptr > right_ptr)
        {
            break;
        }
        else
        {
            left_ptr = right_ptr ^ left_ptr;
            right_ptr = right_ptr ^ left_ptr;
            left_ptr = right_ptr ^ left_ptr;
        }
    }

    left_ptr = right ^ left_ptr;
    right = right ^ left_ptr;
    left_ptr = right ^ left_ptr;
    return left_ptr;
}