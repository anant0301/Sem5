#include "headers.h"

int main(int argc, char const *argv[])
{
	
	int n;
	int k = 20;
	int fib[k + 1];
	long long int fibn;
	char fileName[] = "tmpfile";
	FILE *fp;
	if(argc != 2)
	{
		printf("Enter 1 argument <n> to get the nth term of fibonacci series\n");
		exit(0);
	}
	n = atoi(argv[1]);
	fib[0] = 0;
	fib[1] = 1;
	for(int i = 2; i <= k + 1 && i <= n; ++i)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	if(n <= k)
	{
		printf("Fib Series %d element: %d\n", n, fib[n]);
		exit(0);
	}
	
	clock_t clk = clock(); 
	pid_t pid;
	while((pid = fork()) < 0)
	{
		printf("Fork Failed\n");
	}
	if(pid == 0)
	{
		fp = fopen(fileName, "w");
		fprintf(fp, "%lld\n", fibonacci_series(fib, n - k - 1, k));
		fclose(fp);
		exit(1);
	}
	else
	{
		fibn = fibonacci_series(fib, n - k, k);
		fibn *= fib[k + 1];
		long long int temp;
		wait(NULL);
		fp = fopen(fileName, "r");
		fscanf(fp, "%lld", &temp);
		temp *= fib[k];
		fibn += temp;
	}
	clk = clock() - clk;
	printf("Time Taken fibonacci_series: %lf\n", ((double)clk) / CLOCKS_PER_SEC);
	printf("Fib(%d) %lld\n", n, fibn);
	printf("Parallel_Fib(%d) %lld\n", n, fib_series_parallel(fib, n, k));
	clk = clock() - clk;
	printf("Time Taken fib_series_parallel: %lf\n", ((double)clk) / CLOCKS_PER_SEC);

	return 0;
}
