#include "headers.h"
int main(int argc, char  *argv[])
{
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	pid_t pid = fork();
	int offset;
	if(pid < 0)
	{
		printf("Fork Failure\n");
		exit(0);
	}
	else if(pid == 0)
	{
		offset = 1;
	}
	else
	{
		offset = 0;
	}
	for(int i = (m < n ? m : n) + offset; i < (n < m ? m : n); i += 2)
	{
		if(is_armstrong(i))
		{
			printf("Armstrong Number %d \n", i);
		}
	}
	return 0;
}
