#ifndef headers
#define headers

#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

#define LIMIT 1000

int binary_search(int x, int arr[], int beg, int end);
int lower_bound(int x, int arr[], int beg, int end, char fileName[]);
int upper_bound(int x, int arr[], int beg, int end, char fileName[]);
void random_fill(int arr[], int len);

#endif
