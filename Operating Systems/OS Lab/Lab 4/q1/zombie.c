#include"headers.h"
int main()
{
    pid_t pid;
    while((pid = fork()) < 0);
    if(pid == 0)
    {
        /* Child */
        printf("Child process %d completed... Parent initiated %d \n", getpid(), getppid());
        exit(0);
    }else
    {
        /* Parent */
        printf("Parent will now wait for child\n");
        sleep(10);
        printf("Parent will now wait for child\n");
        while(wait(NULL) >= 0);
        printf("Parent knows child is no more\n");
    }

    return 1;
}