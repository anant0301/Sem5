#include"headers.h"
int randomfill(int arr[], int len)
{
	for(int i = 0; i < len; ++i)
	{
		arr[i] = rand() % LIMIT;
	}
	return 0;
}