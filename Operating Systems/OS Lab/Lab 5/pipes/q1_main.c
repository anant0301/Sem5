#include "headers.h"
extern int reverse(char in_string[], int str_len, char out_string[]);
int main()
{
    char input[MAX_STR_LEN];// = "this is to be reversed";
    char buf[MAX_STR_LEN];
    int fd1[2];
    int fd2[2];
    pid_t pid;
    fgets(input, MAX_STR_LEN, stdin);
    if (pipe(fd1) == -1)
    {
        printf("Piping error\n");
        return 0;
    }
    if (pipe(fd2) == -1)
    {
        printf("Piping error\n");
        return 0;
    }
    if((pid = fork()) < 0)
    {
        printf("Forking Failure\n");
        return 0;
    }
    else if(pid == 0)
    {
        close(fd1[WRITE_END]);
        close(fd2[READ_END]);
        read(fd1[READ_END], buf, MAX_STR_LEN);
        close(fd1[READ_END]);
        char out_string[MAX_STR_LEN];
        reverse(buf, strlen(buf), out_string);
        write(fd2[WRITE_END], out_string, MAX_STR_LEN);
        close(fd2[WRITE_END]);
    }
    else
    {
        close(fd1[READ_END]);
        close(fd2[WRITE_END]);
        printf("Input String: %s\n", input);
        write(fd1[WRITE_END], input, MAX_STR_LEN);
        close(fd1[WRITE_END]);
        read(fd2[READ_END], buf, MAX_STR_LEN);
        close(fd2[READ_END]);
        printf("Reversed String: %s\n", buf);
    }
    return 0;
}