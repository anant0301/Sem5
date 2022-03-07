#include "headers.h"

int randomfill(struct matrix *mat)
{
	for(int i = 0; i < mat->row; ++i)
	{
		for(int j = 0; j < mat->col; ++j)
		{
			mat->arr[i][j] = rand() % RANDOM_NUMBER_LIMIT;
		}
	}	
	return 1;
}
