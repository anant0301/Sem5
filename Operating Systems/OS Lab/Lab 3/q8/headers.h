#ifndef headers
#define headers

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <time.h>
#include<sys/stat.h>
#include <string.h>

#define SIZE 64

long long int fib_series_parallel(int arr[], int n, int k);
long long int fibonacci_series(int arr[], int n, int k);
int cfileexists(const char* filename);

#endif
