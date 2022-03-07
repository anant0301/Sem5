#include"headers.h"
int main(int argc, char *argv[])
{
	int len = argc - 1;
	int arr[len];
	for(int i = 0; i < len; ++i)
	{
		arr[i] = atoi(argv[i + 1]);
	}
	pid_t pid = fork();
	if(pid == -1)
	{
		printf("Fork failure\n");
		exit(0);
	}
	else if(pid == 0)
	{
		printf("Even array elements: \n");
		for(int i = 2; i < len; i += 2)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
	else
	{
		printf("Odd array elements: \n");
		for(int i = 1; i < len; i += 2)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
	return 0;
}
