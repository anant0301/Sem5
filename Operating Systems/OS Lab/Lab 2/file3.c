#include"headers.h"
int main ()
{
  printf("This will be printed ?.\n");
  fork();
  printf("This will be printed ?.\n");
  fork();
  printf("This will be printed ? .\n");
  fork();
  printf("This will be printed ?\n");
  return 0;
}
