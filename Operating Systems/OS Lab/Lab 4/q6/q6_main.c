#include "headers.h"

int main(int argc, char const *argv[])
{
	/*
	the input to the file is the 3 dimension:
	matrix_1_row matrix_1_col matrix_2_row
	the dimension matrix_2_row is always equal to matrix_1_row
	*/
	int m = atoi(argv[1]);
	int p = atoi(argv[2]);
	int n = atoi(argv[3]);
	
	struct matrix* matrix_1 = createMatrix(m, p);
	randomfill(matrix_1);
	printf("Matrix_1\n");
	printMatrix(matrix_1);
	struct matrix* matrix_2 = createMatrix(p, n);
	randomfill(matrix_2);
	printf("Matrix_2\n");
	printMatrix(matrix_2);

	printf("Matrix Product: Matrix_1 * Matrix_2\n");
	struct matrix* pro = matrixMultiply(matrix_1, matrix_2);
	printMatrix(pro);
	
	return 0;
}