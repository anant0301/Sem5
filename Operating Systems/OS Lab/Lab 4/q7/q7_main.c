#include "headers.h"

int main(int argc, char *argv[])
{
	int order;
	char *fileName = argv[1];
	FILE *fp = fopen(fileName, "r");
	fscanf(fp, "%d", &order);
	int *arr[order];
	// read the matrix from the file
	for (int i = 0; i < order; ++i)
	{
		arr[i] = (int *)malloc(order * sizeof(int));
		for (int j = 0; j < order; ++j)
		{
			fscanf(fp, "%d", &arr[i][j]);
		}
	}

	printf("%d\n",check_magic_square(arr, order));

	// print the matrix
	for (int i = 0; i < order; ++i)
	{
		for (int j = 0; j < order; ++j)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}