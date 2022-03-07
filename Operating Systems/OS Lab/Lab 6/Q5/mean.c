#include "../headers.h"
#include "header_q5.h"
void * mean(void * param)
{
    struct q5_param * this = (struct q5_param *)param;
    float *mean = (float*)malloc(sizeof(float));
    long int sum = 0;
    for (int i = 0; i < this-> len; i++)
    {
        sum += this-> arr[i];
    }
    *mean = ((float)sum) / this-> len;
    return mean;
}