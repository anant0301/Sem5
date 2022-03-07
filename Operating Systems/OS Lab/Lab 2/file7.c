#include"headers.h"
int main()
{
	printf("Parent 1\n");	 	// original parent
	pid_t pid = fork();  	// fork 1--> 2
	if(pid == 0)
	{
		printf("Child 2\n");
		pid = fork();				// fork 2--> 4
		if(pid == 0)
		{		
			printf("Child 4\n");
			pid = fork();			// fork 4--> 8
			if(pid == 0)
			{
				printf("Child 8\n");
			}
			else if(pid < 0)
			{
				printf("Fork Failed\n");
			}
		}
		else if(pid > 0)
		{
			pid = fork(); 		// fork 2--> 5
			if(pid == 0)
			{
				printf("Child 5\n");
				pid = fork();		// fork 5--> 9
				if(pid == 0)
				{
					printf("Child 9\n");
				}
				else if(pid < 0)
				{
					printf("Fork Failed\n");
				}
			}
			else if(pid > 0)
			{
				pid = fork();		// fork 2--> 6
				if(pid == 0)
				{
					printf("Child 6\n");
				}
				else if(pid < 0)
				{
					printf("Fork Failed\n");
				}
			}
			else
			{
				printf("Fork Failed\n");
			}
		}
		else
		{
			printf("Fork Failed\n");
		}
	}
	else if(pid > 0)
	{
		printf("Child 3\n");
		pid = fork();				// fork 1--> 3
		if(pid == 0)
		{
			printf("Child 7\n");	
		}	
		else if(pid < 0)
		{
			printf("Fork Failed\n");
		}
	}	
	else
	{
		printf("Fork Failed\n");
	}
	return 0;
}
