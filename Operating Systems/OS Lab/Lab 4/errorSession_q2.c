#include "headers.h"
int mergeSort(int arr[], int begin, int end)
{
	/* 
	int arr[]	: array or part of it to be sorted
	arr[begin]	: the first element considered
	arr[end - 1]: the last element considered
	*/
	if(begin >= end)
	{
		/* 	base case	*/
		return -1;
	}
	/* middle element	 */
	int mid = begin + (end - begin) / 2;
	if (mid > begin)
	{
		/*	recursive calls	*/
		mergeSort(arr, begin, mid);
		mergeSort(arr, mid, end);
		/*	multi-processing and inter-process communication	*/
		pid_t pid;
		/*	file for inter-process communication	*/
		char fileName[] = "./tmp/_____.txt";
		/*	the begin element that are used in char	*/
		fileName[6] = begin / 10 + 48;
		fileName[7] = begin + 48;
		fileName[9] = mid / 10 + 48;
		fileName[10] = mid + 48;
		/*	in case of fork failure fork again	*/
		while((pid = fork()) < 0)
		{
			printf("Fork Failed\n");
		}
		if(pid == 0)
		{
			/*	child process	*/
 			mergeBack(arr, begin, mid, end, fileName);
 			exit(0);
		}
		else
		{
			/*	parent process	*/
			char ch[STR_SIZE];
			printf("File Read:\t%s\n", fileName);
			FILE *fp = fopen(fileName, "r");
			/*	wait till child is done with the process	*/
			waitpid(pid, NULL, 0);
			for(int i = begin; i < end; ++i)
			{
				fscanf(fp, "%d ", &arr[i]);
				bzero(ch,STR_SIZE);
			}
			fclose(fp);
		}
	}
	return 0;
}
