#include "../headers.h"
void random_fill(int **arr, int order)
{
    
    for (int i = 0; i < order; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * order);
        for (int j = 0; j < order; j++)
        {
            arr[i][j] = rand() % 10;
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}