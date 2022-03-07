#ifndef headers
#define headers
/*provides standard input output functions 
here: printf() and scanf()*/
#include<stdio.h>
/*provides standard function in the library 
here: atoi(), remove() and rand(), it even includes the data type pid_t*/
#include<stdlib.h>
/*provides access to the POSIX operating system API 
here: fork()*/
#include<unistd.h>
/*provides symbolic constants for use with waitpid(): WNOHANG,etc 
here: waitpid()*/
#include<sys/wait.h>
/*provides string related functions 
here: bzero()*/
#include<string.h>

/* the interprocess communication uses files the integer stored in the files can be of 
max string length = STR_LENGTH  
*/
#define STR_SIZE 100

int mergeSort(int arr[], int begin, int end);
int mergeBack(int arr[], int begin, int mid, int end, char fileName[]);
int randomfill(int arr[], int len, int limit);

#endif
