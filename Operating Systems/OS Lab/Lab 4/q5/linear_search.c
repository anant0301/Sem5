#include"headers.h"

int linear_search(char arr[], char ch, int len)
{
	int count = 0;
	for(int i = 0; i < len; ++i)
	{
		if(arr[i] == ch)
		{
			count++;
		}
	}
	return count;
}