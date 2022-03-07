#ifndef headers
#define headers

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int first_greater(int a, int b);
int first_smaller(int a, int b);
int sort(int arr[], int len,  int compare(int,  int));

#endif