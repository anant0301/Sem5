#include "headers.h"

int main(int argc, char const *argv[])
{
	int len;
	len = atoi(argv[1]);
	// len = argc - 1;
	int arr[len];
	// for(int i = 0; i < len; ++i)
	// {
	// 	arr[i] = atoi(argv[i + 1]);
	// }
	randomfill(arr, len);
	for(int i = 0; i < len; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	mergeSort(arr, 0, len);
	char fileName[STR_SIZE];
	printf("The sorted order for the above is \n");
	sprintf(fileName, "./tmp/%d-%d", 0, len);
	
	FILE *fp = fopen(fileName, "r");
	for(int i = 0; i < len; ++i)
	{
		fscanf(fp, "%d ", &arr[i]);
		printf("%d ", arr[i]);
	}
	printf("\n");
	fclose(fp);
	
	
	pid_t pid = vfork();
	if(pid == 0)
	{

		char cmd[] = "rm";
		char *arg[] = {
			"rm", fileName, NULL
		};
		execvp(cmd, arg);
	}
	else
	{
		wait(NULL);
		printf("The files are deleted\n");
	}
	return 0;
}
