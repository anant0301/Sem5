#include "../headers.h"
#include "header_q5.h"

void * median(void * param)
{
    struct q5_param * this = (struct q5_param *)param;
    
    float *median = (float*)malloc(sizeof(float));
    if(this-> len % 2)
    {
        *median = (this-> arr[this-> len / 2] + this-> arr[this-> len / 2])/ 2.00;
    }
    else
    {
        *median = this-> arr[this-> len / 2];
    }
    return  median;
}