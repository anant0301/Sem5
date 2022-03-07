#include "../headers.h"
void random_fill(int arr[], int len)
{
	if (len > 0)
	{ 
		arr[0] = rand() % 10;
		for(int i = 1; i < len; ++i)
		{
			arr[i] = rand() % 1000;
		}
	}
}