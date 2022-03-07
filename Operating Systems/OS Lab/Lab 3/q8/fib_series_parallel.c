#include "headers.h"

long long int fib_series_parallel(int arr[], int n, int k)
{
	if(n <= k + 1)
	{
		return arr[n];
	}
	else
	{
		pid_t pid;
		FILE *fp;
		char fileName[SIZE];
		while((pid = fork()) < 0)
		{
			printf("Fork Failed in fib_series\n");
		}
		if(pid == 0)
		{
			if(n-k-1 > k+1)
			{
				sprintf(fileName, "./tmp/%d.txt", n - k - 1);
				if(cfileexists(fileName) == 0)
				{
					fp = fopen(fileName, "w");
					fprintf(fp, "%lld\n", fib_series_parallel(arr, n - k - 1, k));
					fclose(fp);
				}
			}
			exit(0);
		}
		else
		{
			long long int fib_n_k;
			long long int fib_n_k_1;
			if(n - k > k)
			{
				sprintf(fileName, "./tmp/%d.txt", n - k);
				if(cfileexists(fileName) == 0)
				{
					fib_n_k = fib_series_parallel(arr, n - k, k);
					fp = fopen(fileName, "w");
					fprintf(fp, "%lld\n", fib_n_k);
					fclose(fp);
				}
			}
			else
			{
				fib_n_k = arr[n - k];
			}
			wait(NULL);
			if(n - k - 1 > k)
			{
				bzero(fileName, SIZE);
				sprintf(fileName, "./tmp/%d.txt", n - k - 1);
				if(cfileexists(fileName))
				{	
					fp = fopen(fileName, "r");
					fscanf(fp, "%lld", &fib_n_k_1);
					fclose(fp);
					fib_n_k = fib_series_parallel(arr, n - k -1, k);
				}
			}
			else
			{
				fib_n_k_1 = arr[n - k - 1];
			}
				return fib_n_k_1 * arr[k] + fib_n_k * arr[k + 1];
		}
	}
}
