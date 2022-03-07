#include "headers.h"

int printMatrix(struct matrix *m)
{
	for(int i = 0; i < m->row; ++i)
	{
		for(int j = 0; j < m->col; ++j)
		{
			printf("%d\t\t", m->arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}