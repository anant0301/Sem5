#include "../headers.h"
#include "header_q8.h"
extern void * determinant(void * param);
void * cofactor(void * param)
{
    struct cofactor_param * this = (struct cofactor_param*)param;
    int **arr = this-> arr; 
    int order = this-> order;
    int missing_row = this-> missing_row;
    int missing_col = this-> missing_col;

    int *partial_mat[order - 1];
    for (int i = 0; i < order - 1; i++)
    {
        partial_mat[i] = (int *)malloc(sizeof(int) * (order - 1));
    }
    for (int i_ = 0, i = 0; i < order; i++, i_++)
    {
        if(i == missing_row)
        {
            i_--;
            continue;
        }
        for (int j_ = 0, j = 0; j < order; j++, j_++)
        {
            if(j == missing_col)
            {
                j_--;
                continue;
            }
            partial_mat[i_][j_] = arr[i][j];
        }
    }
    struct determinant_param * new = (struct determinant_param *)malloc(sizeof(struct determinant_param));
    new-> arr = partial_mat;
    new-> order = order - 1;
    new-> determinant = 0;
    determinant(new);
    return &new-> determinant;
}