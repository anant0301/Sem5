#include"headers.h"
int fib_series(int n)
{
	int arr[n];
	
	arr[0] = 0;
	arr[1] = 1;
	for(int i = 2; i < n ; ++i)
	{
		arr[i] = arr[i-1] + arr[i-2];
	}
	printf("Fib Series: ");
	for(int i = 0; i < n ; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0; // success printing
}
