#include "headers.h"
int main(int argc, char *argv[])
{
    char str_1[MAX_STR_LEN] = "This is string 1...";
    char str_2[MAX_STR_LEN] = "This is string 2...";
    int fd1[2];
    int fd2[2];
    pid_t pid;
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
        read(fd1[READ_END], str_1, MAX_STR_LEN);
        close(fd1[READ_END]);
        printf("String 2: %s\n", str_2);
        strcat(str_1, str_2);
        write(fd2[WRITE_END], str_1, MAX_STR_LEN);
        close(fd2[WRITE_END]);
    }
    else
    {
        close(fd1[READ_END]);
        close(fd2[WRITE_END]);
        printf("String 1: %s\n", str_1);
        write(fd1[WRITE_END], str_1, MAX_STR_LEN);
        close(fd1[WRITE_END]);
        read(fd2[READ_END], str_2, MAX_STR_LEN);
        close(fd2[READ_END]);
        printf("Concatenated String: %s\n", str_2);
    }
    return 0;
}