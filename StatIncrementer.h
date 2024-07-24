#include "StatDecorator.h"

class StatIncrementer : public StatDecorator
{
   int increment;

public:
   StatIncrementer(const int &increment, Stat *s) : StatDecorator{s}, increment{increment} {}
   int getStat() const override;
};