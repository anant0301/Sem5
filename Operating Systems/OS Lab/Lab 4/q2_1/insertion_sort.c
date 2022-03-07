#include "headers.h"
void insertion_sort(int arr[], int len)
{
	for (int i = 1; i < len; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if(arr[i] < arr[j])
			{
				arr[i] = arr[i] ^ arr[j];
				arr[j] = arr[i] ^ arr[j];
				arr[i] = arr[i] ^ arr[j];
			}
		}
	}
}