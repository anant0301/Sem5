#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include<unistd.h>
#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define INPUT_BUFFER_SIZE 100
#define READ_PIPE 0
#define WRITE_PIPE 1
#define BUFFER_SIZE 10

int check_magic_square(int *arr[], int order);

#endif