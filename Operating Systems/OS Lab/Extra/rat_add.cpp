#include "headers.h"

Rational* Rational::rat_add(Rational *rat)
{
  return (new Rational(this->n * rat->d + this->d * rat->n, this->d * rat->d));
}
