#include"headers.h"
int write_to_matrix(struct matrix* m, char fileName[])
{
	FILE *rfp = fopen(fileName, "r");
	int i;
	int j;
	int pro;
	while(fscanf(rfp, "%d %d %d\n", &i, &j, &pro) != EOF)
	{
		m->arr[i][j] = pro;
	}
	return 0;
}
