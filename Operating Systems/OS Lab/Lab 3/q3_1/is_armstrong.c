#include"headers.h"
int is_armstrong(int num)
{
	int n = num;
	pid_t pid;
	FILE *fp;
	int temp;
	char fileName[] = "tmpFile"; 
	while((pid = fork()) < 0)
	{
		printf("Fork Failed\n");
	}
	if(pid == 0)
	{
		fp = fopen(fileName, "w");
		while(n)
		{
			temp = (n % 10);
			fprintf(fp, "%d ", temp * temp * temp);
			n /= 10;
		}
		fclose(fp);
		exit(0);
	}
	else
	{
		wait(NULL);
		fp = fopen(fileName, "r");
		while(fscanf(fp, "%d ", &temp) >= 0)
		{
			n -= temp;
		}
	}
	if(n)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
