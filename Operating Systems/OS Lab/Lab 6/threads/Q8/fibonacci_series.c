#include "../headers.h"
long long int fibonacci_series(int arr[], int n, int k)
{
	if(n <= k + 1)
	{
		return arr[n];
	}
	return fibonacci_series(arr, n - k - 1, k) * arr[k] + fibonacci_series(arr, n - k, k) * arr[k + 1];
}
