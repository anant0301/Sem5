#include "../headers.h"
#include "header_q8.h"
extern void random_fill(int **arr, int order);
extern void * determinant(void * param);
extern void inverse(struct determinant_param * this);
int main(int argc, char *argv[])
{
    int order = atoi(argv[1]);
    int *arr[order];
    random_fill(arr, order);
    struct determinant_param* init = (struct determinant_param*)malloc(sizeof(struct determinant_param));
    init-> arr = arr;
    init-> order = order;
    init-> determinant = 0;
    determinant(init);
    printf("Determinant Value: %d\n", init-> determinant);
    inverse(init);
    return 0;
}