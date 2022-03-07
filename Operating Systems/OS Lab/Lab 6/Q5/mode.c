#include "../headers.h"
#include "header_q5.h"
void * mode (void * param)
{
    struct q5_param * this = (struct q5_param *)param;
    int *mode = (int *)malloc(sizeof(int) * 2);
    // mode[0] --- element in the array
    // mode[1] --- frequency of the element in mode[0]
    int x = this-> arr[0];
    int freq;
    mode[1] = 0;
    for (int i = 0; i < this-> len; i++)
    {
        x = this-> arr[i];
        freq = 0;
        while(this-> arr[i] == x)
        {
            ++i;
            ++freq;
        }
        if(freq > mode[1])
        {
            mode[0] = x;
            mode[1] = freq;
        }
    }
    
    return mode;
}