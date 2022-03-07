#include "headers.h"
int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	pid_t pid = fork();
	if(pid < 0)
	{
		printf("Fork Failure\n");
		exit(0);
	}
	else if(pid == 0)
	{
		// prime series till n
		printf("Prime Series: ");
		for(int i = 0; i < n; ++i)
		{
			if(is_prime(i))
			{
				printf("%d ", i);
			}
		}
		printf("\n");
	}
	else
	{
		// fibonacci series till n
		fib_series(n);
	}
	return 0;
}
