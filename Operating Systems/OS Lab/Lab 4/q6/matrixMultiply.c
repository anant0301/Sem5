#include"headers.h"

struct matrix* matrixMultiply(struct matrix *m1, struct matrix *m2)
{
	pid_t pid;
	struct matrix* pro = createMatrix(m1->row, m2->col);
	char fileName[] = "Product.txt";
	FILE *wfp = fopen(fileName, "w");
	fclose(wfp);
	for(int i = 0; i < m1->row; ++i)
	{
		for(int j = 0; j < m2->col; ++j)
		{
			while((pid = fork()) < 0)
			{
				printf("Fork Failed\n");
			}
			if(pid == 0)
			{
				wfp = fopen(fileName, "a");
				fprintf(wfp, "%d %d %d\n", i, j, multiply_row_col(m1, i, m2, j));
				fclose(wfp);
				exit(1);
			}
		}
	}
	while ((pid = wait(NULL)) > 0);
	write_to_matrix(pro, fileName);
	return pro;
}