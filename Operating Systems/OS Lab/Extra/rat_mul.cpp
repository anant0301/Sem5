#include "headers.h"

Rational* Rational::rat_mul(Rational *rat)
{
  return (new Rational(this->n * rat->n, this->d * rat->d));
}
