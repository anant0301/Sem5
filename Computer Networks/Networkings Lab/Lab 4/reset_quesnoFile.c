#include"./headers/headers.h"
int	reset_quesnoFile()
{
	FILE *fwp = fopen("ques_no_file.txt", "w");
	char ch = '1';
	fputc(ch, fwp);
	fclose(fwp);
	return 0;
}
