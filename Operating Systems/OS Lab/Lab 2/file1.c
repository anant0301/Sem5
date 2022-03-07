#include"headers.h"
int main()
{
  pid_t pid1, pid2, pid3;
	pid1 = pid2 = pid3 = -1;
  pid1=fork();
  if (pid1!=0)
    pid2 = fork();
  pid3 = fork();
  printf("Count %d %d %d\n",pid1, pid2, pid3);
  return 0;
}
