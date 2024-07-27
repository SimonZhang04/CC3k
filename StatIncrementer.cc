#include "StatIncrementer.h"

float StatIncrementer::getStat() const
{
   return next->getStat() + increment;
};
