#ifndef headers
#define headers

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARG_SIZE 256
#define MAX_CMD_SIZE 256
#define INPUT_BUFFER_SIZE 1024
#define KGRN  "\x1B[32m"
#define KBLU  "\x1B[34m"
#define KWHT  "\x1B[37m"
#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[0m"


int input(char input_buf[], char *arg[]);
void reset(char cmd[], char *arg[], int len);

#endif
