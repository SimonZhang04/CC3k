#include "Stat.h"

class StatDecorator : public Stat
{
protected:
   Stat *next;

public:
   StatDecorator(Stat *s) : next{s} {}
   virtual ~StatDecorator();
};