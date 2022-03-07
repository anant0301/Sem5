#include"headers.h"
int main()
{
    pid_t pid;
    while((pid = fork()) < 0);
    if(pid == 0)
    {
        /* Child */
        sleep(1);
        printf("Child now orphaned %d\n", getppid());
    }else
    {
        /* Parent */
        exit(0);
    }
    
    return 1;
}