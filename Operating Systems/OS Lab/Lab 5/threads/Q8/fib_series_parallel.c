#include "../headers.h"
#include "header_q8.h"
extern long long int fibonacci_series(int arr[], int n, int k);
long long int fib_series_parallel(void * param)
{
	struct q8_main* temp = param;
	int *arr = temp-> arr;
	int n = temp-> n;
	int k = temp-> k;
	if(n <= k + 1)
	{
		return (long long int)arr[n];
	}
	else
	{
		long long int fib_n_k = fibonacci_series(arr, n - k, k);
		long long int fib_n_k_1 = fibonacci_series(arr, n - k - 1, k);
		return fib_n_k_1 * arr[k] + fib_n_k * arr[k + 1];
	}
}
