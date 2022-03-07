#include"headers.h"

int main(int argc, char const *argv[])
{
	printf("The given arguments will be sorted...\n");
	int len = argc - 1;
	int arr[len];
	pid_t pid;
	FILE *fp;
	char fileName[] = "tmp.txt";
	for (int i = 0; i < len; ++i)
	{
		arr[i] = atoi(argv[i + 1]);
	}
	if(len > 2)
	{
		while((pid = fork()) < 0)
		{
			printf("Fork Failed\n");
		}
		if(pid == 0)
		{
			sort(arr, len , first_smaller);
			for(int i = 0; i < len; ++i)
			{
				printf("%d ", arr[i]);
			}
			printf("\n");
			exit(0);
		}
		else
		{
			sort(arr, len, first_greater);
		}
	}
	wait(NULL);
	
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
