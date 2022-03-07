#include "./headers/headers.h"

int get_quesno()
{
	FILE *frp = fopen("ques_no_file.txt", "r");
	char ch[BUFFER_SIZE];
	fgets(ch, BUFFER_SIZE, frp);
	fclose(frp);
	int qno = atoi(ch);
	FILE *fwp = fopen("ques_no_file.txt", "w");
	bzero(ch, BUFFER_SIZE);
	sprintf(ch, "%d\n", qno + 1);
	fputs(ch, fwp);
	fclose(fwp);
	return qno;
}
