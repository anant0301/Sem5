#include "headers.h"
int mergeSort(int arr[], int begin, int end)
{
	if(begin >= end)
	{
		return 0;
	}
	int mid = begin + (end - begin) / 2;
	// pid_t pid = fork();
	if (mid > begin)
	{
		int begl = mergeSort(arr, begin, mid);
		int begr = mergeSort(arr, mid, end);
		pid_t pid;
		char fileName[] = "./tmp/___.txt";
		fileName[6] = begl + 48;
		fileName[8] = begr + 48;
		while((pid = fork()) < 0)
		{
			printf("Fork Failed\n");
		}
		if(pid == 0)
		{
 			mergeBack(arr, begin, mid, end, fileName);
 			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			char ch[STR_SIZE];
			FILE *fp = fopen(fileName, "r");
			for(int i = begin; i < end; ++i)
			{
				fscanf(fp, "%d ", &arr[i]);
				bzero(ch,STR_SIZE);
			}
			fclose(fp);
		}
	}
	return begin;
}
