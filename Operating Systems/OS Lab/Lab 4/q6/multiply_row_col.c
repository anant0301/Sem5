#include "headers.h"

int multiply_row_col(struct matrix *m1, int row, struct matrix *m2, int col)
{
	int sum = 0;
	for(int i = 0; i < m1->col; ++i)
	{
		sum += m1->arr[row][i] * m2->arr[i][col];
	}
	return sum;
}