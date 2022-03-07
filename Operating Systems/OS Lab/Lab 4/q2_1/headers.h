#ifndef headers
#define headers

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define STR_SIZE 100
#define LIMIT 1000

int mergeSort(int arr[], int begin, int end);
int mergeBack(int begin, int mid, int end);
int randomfill(int arr[], int len);
void insertion_sort(int arr[], int len);

#endif