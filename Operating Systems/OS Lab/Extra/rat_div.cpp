#include "headers.h"

Rational* Rational::rat_div(Rational *rat)
{
  return (new Rational(this->n * rat->d, this->d * rat->n));
}
