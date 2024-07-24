#include "StatIncrementer.h"

int StatIncrementer::getStat() const
{
   return next->getStat() + increment;
};
