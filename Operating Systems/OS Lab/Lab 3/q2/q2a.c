#include"headers.h"
int main(int argc, char *argv[])
{
	int len = atoi(argv[1]);
		
	pid_t pid = fork();
	if(pid == -1)
	{
		printf("Fork failure\n");
		exit(0);
	}
	else if(pid == 0)
	{
		printf("Child Block even Series\n");
		for(int i = 0; i < len; i += 2)
		{
			printf("%d ", i);
		}
		printf("\n");
	}
	else
	{
		printf("Parent Block odd Series\n");
		for(int i = 1; i < len; i += 2)
		{
			printf("%d ", i);
		}
		printf("\n");
	}
	return 0;
}
