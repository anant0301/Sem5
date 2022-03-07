#include "headers.h"

int input(char input_buf[], char *arg[])
{
	int k = 0;
	int len = strlen(input_buf);
	for (int i = 0; i < len; ++i)
	{
		arg[k] = (char *)malloc(sizeof(char) * MAX_CMD_SIZE);
		for (int j = 0; input_buf[i] != ' ' && input_buf[i] != '\n' && i < len; ++j, ++i)
		{
			if(input_buf[i] == '\\')
			{
				i++;				
			}
			arg[k][j] = input_buf[i];
		}
		++k;
	}
	arg[k] = NULL;
	return k;
}