#include "headers.h"
struct matrix* createMatrix(int row, int col)
{
	struct matrix *m = (struct matrix*)malloc(sizeof(struct matrix));
	m->row = row;
	m->col = col;
	m->arr = (int**)malloc(row * sizeof(int*));
	for(int i = 0; i < row; ++i)
	{
		m->arr[i] = (int*)malloc(col * sizeof(int));
	}	
	return m;
}	