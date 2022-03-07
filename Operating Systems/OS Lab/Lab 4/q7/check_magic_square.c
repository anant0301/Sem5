#include "headers.h"
int check_magic_square(int *arr[], int order)
{
	pid_t pid;
	int fd[2];
	int sum = 0;
	int magic_number;
	int bytesRead;
	char buf[BUFFER_SIZE];
	pipe(fd);
	while((pid = fork()) < 0)
	{
		printf("Fork Failed\n");
	}
	if(pid == 0)
	{
		while((pid = fork()) < 0)
		{
			printf("Fork Failed\n");
		}		
		if(pid == 0)
		{	// check row sum
			for (int i = 0; i < order; ++i)
			{
				sum = 0;
				for (int j = 0; j < order; ++j)
				{
					sum += arr[i][j];
				}
				sprintf(buf, "%d ", sum);
				write(fd[WRITE_PIPE], buf, BUFFER_SIZE);
				memset(buf, 0, BUFFER_SIZE);
			}
			exit(0);
		}
		else 
		{
			// check column sum
			for (int i = 0; i < order; ++i)
			{
				sum = 0;
				for (int j = 0; j < order; ++j)
				{
					sum += arr[j][i];
				}
				sprintf(buf, "%d ", sum);
				write(fd[WRITE_PIPE], buf, BUFFER_SIZE);
				memset(buf, 0, BUFFER_SIZE);
			}
			exit(0);	
		}
	}
	else
	{

		magic_number = ((order * order + 1) * order) / 2;
		for (int i = 0; i < order; ++i)
		{
			sum += arr[i][i];
		}
		if (magic_number != sum)
		{
			return 0;
		}
		sum = 0;
		for (int i = 0; i < order; ++i)
		{
			sum += arr[i][order - 1- i];

		}
		if(magic_number != sum)
		{
			return 0;
		}	
		do
		{
			bytesRead = read(fd[READ_PIPE], buf, BUFFER_SIZE);
			if((sum = atoi(buf)) != magic_number)
			{
				return 0;
			}
				// printf("Sm send %s\n", buf);
			// printf("Sm received: %d %d\n", sum, magic_number);
		}while(wait(NULL) > 0);
		return 1;
	}
}