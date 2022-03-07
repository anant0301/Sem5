#include "../headers.h"
#include "header_q8.h"
void * determinant(void * param)
{
    struct determinant_param * this = (struct determinant_param*)param;
    int **arr = this-> arr; 
    int order = this-> order; 
    if(order <= 2)
    {
        if(order == 2)
            this-> determinant += arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
        else if(order == 1)
        {
            this-> determinant += arr[0][0];
        }
        else
        {
            printf("Invalid Input\n");
        }
    }
    else
    {
        int *new_arr[order][order - 1];
        pthread_t tid[order];
        struct determinant_param * next[order];
        for(int i = 0; i < order; ++i)
        {
            for (int k = 0, j = 0; j < order; j++)
            {
                if(j != i)
                {
                    new_arr[i][k++] = &arr[j][1]; 
                }
            }
            next[i] = (struct determinant_param *)malloc(sizeof(struct determinant_param));
            next[i]-> arr = new_arr[i];
            next[i]-> order = order - 1;
            next[i]-> determinant = 0;
            pthread_create(&tid[i], NULL, determinant, next[i]);
        }
        for (int i = 0, k = 1; i < order; i++, k *= -1)
        {
            pthread_join(tid[i], NULL);
            this-> determinant += arr[i][0] * next[i]-> determinant * k;
        }
    }
    return NULL;
}