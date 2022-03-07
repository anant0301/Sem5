#include"headers.h"

int main(int argc, char const *argv[])
{
	printf("The first half is descending and second half ascending\n");
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
			sort(arr, len / 2, first_smaller);
			fp = fopen(fileName, "w");
			for(int i = 0; i < len / 2; ++i)
			{
				fprintf(fp, "%d ", arr[i]);
			}
			fprintf(fp, "\n");
			fclose(fp);
			exit(0);
		}
		else
		{
			sort(&arr[len / 2], len - len / 2, first_greater);
		}
	}
	wait(NULL);
	fp = fopen(fileName, "r");
	for (int i = 0; i < len / 2; ++i)
	{
		fscanf(fp, "%d ", &arr[i]);
	}
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
