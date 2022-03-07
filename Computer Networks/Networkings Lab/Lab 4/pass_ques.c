#include"./headers/headers.h"

char pass_ques(int sock, int qno)
{
	char qfile[BUFFER_SIZE] = "./questions/q_.txt";
	char buf[BUFFER_SIZE];
	qfile[13]  = qno + 48;  
	printf("%s\n", qfile);
	FILE *fp = fopen(qfile, "r");
	while(fgets(buf, BUFFER_SIZE, fp))
	{
		write(sock, buf, BUFFER_SIZE);
		bzero(buf, BUFFER_SIZE);
	}
	fclose(fp);
	char ansfile[BUFFER_SIZE] = "./questions/q_ans.txt"; 
	ansfile[13] = qno + 48;
	fp = fopen(ansfile, "r");
	char ch;
	ch = fgetc(fp);
	fclose(fp);
	return ch;
}