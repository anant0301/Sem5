#include "../headers.h"
#include "header_q8.h"
extern void * cofactor(void * param);
void inverse(struct determinant_param * this)
{
    int **arr = this-> arr;
    int order = this-> order;
    if(this-> determinant == 0)
    {
        printf("The Matrix determinant value is 0 hence inverse not possible");
        return;
    }
    else if(order == 1)
    {
        printf("%f\n", 1.00 / arr[0][0]);
        return;
    }
    pthread_t *tid[order];
    struct cofactor_param ** new[order];
    int *cofactor_matrix[order];
    void * return_value;
    for (int i = 0; i < order; i++)
    {
        tid[i] = (pthread_t *)malloc(sizeof(pthread_t) * order);
        new[i] = (struct cofactor_param **)malloc(sizeof(struct cofactor_param*) * order);
        cofactor_matrix[i] = (int *)malloc(sizeof(int) * order);
        for (int j = 0; j < order; j++)
        {
            new[i][j] = (struct cofactor_param*)malloc(sizeof(struct cofactor_param));
            new[i][j]-> arr = arr;
            new[i][j]-> order = order;
            new[i][j]-> missing_col = j;
            new[i][j]-> missing_row = i;
            pthread_create(&tid[i][j], NULL, cofactor, new[i][j]);
        }
    }
    for (int k = 1, i = 0; i < order; i++, k = i % 2 ? -1 : 1)
    {
        for (int j = 0; j < order; j++)
        {
            pthread_join(tid[i][j], &return_value);
            cofactor_matrix[i][j] = *(int *) return_value * k; 
            k *= -1;
        }
    }
    for (int j = 0; j < order; j++)
    {
        for (int i = 0; i < order; i++)
        {
            printf("%f\t ", cofactor_matrix[i][j]/ (double) this-> determinant);
        }
        printf("\n");
        
    }
    
}