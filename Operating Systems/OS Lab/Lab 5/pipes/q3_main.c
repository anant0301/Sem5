#include "headers.h"
int main(int argc, char * argv[])
{
    char string[MAX_STR_LEN] = "This is a string to get it's substring ";
    char substring[MAX_STR_LEN];
    int fd[2][2];
    int beg = atoi(argv[1]);
    int end = atoi(argv[2]);
    char buf[MAX_STR_LEN];
    pid_t pid;
    if(pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
    {
        printf("Piping Failure");
    }
    if((pid = fork()) < 0)
    {
        printf("Fork Failed");
    }
    else if(pid == 0)
    {
        close(fd[1][READ_END]);
        close(fd[0][WRITE_END]);
        read(fd[0][READ_END], buf, MAX_STR_LEN);
        sscanf("%d %d", &beg, &end);
        bzero(string, MAX_STR_LEN);
        read(fd[0][READ_END], string, MAX_STR_LEN);
        if(end > strlen(string) || beg < 0)
        {
            printf("The range exceeds string limits- [0..%ld]\n", strlen(string));
            exit(0);
        }
        for(int i = beg; i < end ; ++i)
        {
            substring[i - beg] = string[i];
        }
        write(fd[1][WRITE_END], substring, MAX_STR_LEN);
        close(fd[0][READ_END]);
    }
    else
    {
        close(fd[1][WRITE_END]);
        close(fd[0][READ_END]);
        sprintf(buf, "%d %d", beg, end);
        printf("String: %s\n", string);
        write(fd[0][WRITE_END], buf, MAX_STR_LEN);
        write(fd[0][WRITE_END], string, MAX_STR_LEN);
        bzero(buf, MAX_STR_LEN);
        close(fd[0][WRITE_END]);
        read(fd[1][READ_END], substring, MAX_STR_LEN);
        printf("Substring: %s\n", substring);
    }
    return 0;
}