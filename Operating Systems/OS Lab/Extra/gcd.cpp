#include "headers.h"

int gcd(int a, int b)
{
  if(b == 1)
    return 1;
  return gcd(b, a % b);
}
