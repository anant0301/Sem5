#include "../headers.h"
#include "header_q7.h"
void * random_point(void * param)
{
    struct q7_parameter* this = (struct q7_parameter*)param;
    int x = rand() % this-> radius;
    int y = rand() % this-> radius;
    if(x * x + y * y < this-> square)
    {
        ++this-> in_circle;
        ++this-> in_square;
    }
    else
    {
        ++this-> in_square;
    }
    return NULL;
}