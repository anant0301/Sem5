#include"headers.h"

int main()
{
	pid_t pid;
	int status;
	long int i = 0;
	char fileName[] = "process_count.txt";
	FILE *fp = fopen(fileName, "w");
	for(i = 0; (pid=fork())>=0; ++i)
	{
		if(pid == 0)
		{
			wait(NULL);
			fprintf(fp, "%d Process exit\n", getpid());
			fclose(fp);
			exit(0);
		}
	};
	wait(NULL);

	printf("Process Number before failure %ld\n", i);
	fclose(fp);
	return 0;
}
