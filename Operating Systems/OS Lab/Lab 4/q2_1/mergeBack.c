#include "headers.h"
int mergeBack(int begin, int mid, int end)
{
	char fileName1[STR_SIZE];
	char fileName2[STR_SIZE];
	char fileName3[STR_SIZE];
	int p1 = begin;
	int p2 = mid;
	int index = 0;

	sprintf(fileName1, "./tmp/%d-%d", begin, mid);
	sprintf(fileName2, "./tmp/%d-%d", mid, end);
	sprintf(fileName3, "./tmp/%d-%d", begin, end);
	
	FILE *fp1 = fopen(fileName1, "r");
	FILE *fp2 = fopen(fileName2, "r");
	FILE *fp3 = fopen(fileName3, "w");
	
	int in1;
	int in2;

	fscanf(fp1, "%d ", &in1);
	fscanf(fp2, "%d ", &in2);

	while(p1 < mid && p2 < end)
	{
		if(in1 > in2)
		{
			fprintf(fp3, "%d ", in2);
			fscanf(fp2, "%d ", &in2);
			p2++;
		}
		else 
		{
			fprintf(fp3, "%d ", in1);
			fscanf(fp1, "%d ", &in1);
			p1++;
		}
		index++;
	}
	while(p1 < mid)
	{
		fprintf(fp3, "%d ", in1);
		fscanf(fp1, "%d ", &in1);
		p1++;
		index++;
	}
	while(p2 < end)
	{
		fprintf(fp3, "%d ", in2);
		fscanf(fp2, "%d ", &in2);
		p2++;
		index++;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	pid_t pid;
	while((pid = vfork()) < 0)
	{
		printf("Fork Failed\n");
	}
	if(pid == 0)
	{
		char cmd[] = "rm";
		char *args[] = {"rm", fileName2, fileName1, NULL};
		execvp(cmd, args);
	}
	return 0;
}