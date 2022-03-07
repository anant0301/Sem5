#include "headers.h"

Rational::Rational(int num, int den);
{
  if (den)
  {
    int g = gcd(num, den);
    this->n = num / g;
    this->d = den / g;
  }
  printf("Invalid Rational created\n");
  exit(0);
}
