#ifndef headers
#define headers

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define IN_STRING_LENGTH 1024

int uniq_element(char string[], char uniq[], int strlen);
int linear_search(char arr[], char ch, int len);

#endif