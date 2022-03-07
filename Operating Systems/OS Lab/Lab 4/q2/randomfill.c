#include"headers.h"
int randomfill(int arr[], int len, int limit)
{
	/*
	int limit: the upper limit that can be there in the array
	int len: the length of the array to be filled
	int arr[]: the array to be filled 
	*/
	srand(1);
	for(int i = 0; i < len; ++i)
	{
		arr[i] = rand() % limit;
	}
	return 0;
}