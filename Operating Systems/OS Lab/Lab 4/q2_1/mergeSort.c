#include "headers.h"
int mergeSort(int arr[], int begin, int end)
{
	if(end - begin <= 3)
	{	
		char fileName[STR_SIZE];
		FILE *fp;

		sprintf(fileName, "./tmp/%d_%d", begin, end);
		fp = fopen(fileName, "w");

		insertion_sort(&arr[begin], end - begin);

		for (int i = begin; i < end; ++i)
		{
			fprintf(fp, "%d ", arr[i]);
		}
		fprintf(fp, "\n");
		fclose(fp);
		return 0;
	}

	int mid = begin + (end - begin) / 2;

	pid_t pid;

	while((pid = fork()) < 0)
	{
		printf("Fork Failed\n");
	}
	if(pid == 0)
	{
		mergeSort(arr, begin, mid);
		exit(0);
	}
	else
	{
		mergeSort(arr, mid, end);
	}
	mergeBack(begin, mid, end);
	waitpid(pid, NULL, 0);
	return 1;
}