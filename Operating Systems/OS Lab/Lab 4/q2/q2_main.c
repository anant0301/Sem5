#include "headers.h"

int main(int argc, char const *argv[])
{
	int len;
	int arr[len];
	
	// len = argc - 1;
	// for(int i = 0; i < len; ++i)
	// {
	// 	arr[i] = atoi(argv[i + 1]);
	// }
	len = atoi(argv[1]);
	randomfill(arr, len, 1000);
	for(int i = 0; i < len; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	mergeSort(arr, 0, len);
	printf("Sorted Array\n");
	for(int i = 0; i < len; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
