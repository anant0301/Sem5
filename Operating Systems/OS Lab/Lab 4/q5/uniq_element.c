#include"headers.h"
int uniq_element(char string[], char uniq[], int strlen)
{
	int len = 0;
	for(int i = 0; i <  strlen ; ++i)
	{
		if(linear_search(string, string[i], i))
		{
			continue;
		}
		else
		{
			uniq[len++] = string[i];
		}
	}
	uniq[len] = '\0';
	return len;
}
