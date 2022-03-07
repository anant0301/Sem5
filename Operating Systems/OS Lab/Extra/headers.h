#pragma once
#include<stdio.h>
#include<stdlib.h>

class Rational
{
public:
  int n;
  int d;
  Rational(int num, int den);
  Rational* rat_add(Rational *rat);
  Rational* rat_sub(Rational *rat);
  Rational* rat_mul(Rational *rat);
  Rational* rat_div(Rational *rat);
};

int gcd(int a, int b);
