#include "headers.h"
int binary_search(int x, int arr[], int beg, int end)
{
	int mid;
	if(beg <= end)
	{
		mid = (end + beg) / 2;
		if(arr[mid] == x)
		{
			return mid;
		}
		else if(arr[mid] > x)
		{
			binary_search(x, arr, beg, mid - 1);
		}
		else if(arr[mid] < x)
		{
			binary_search(x, arr, mid + 1, end);
		}
	}
	else
	{
		return -1;
	}
}