#include "headers.h"
void random_fill(int arr[], int len)
{
	if (len > 0)
	{ 
		arr[0] = rand() % LIMIT;
		for(int i = 1; i < len; ++i)
		{
			arr[i] = arr[i - 1] + rand() % 2;
		}
	}
}