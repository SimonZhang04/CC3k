#include "StatDecorator.h"

class StatMultiplier : public StatDecorator
{
   float multiply;

public:
   StatMultiplier(const float multiply, std::unique_ptr<Stat> s) : StatDecorator{std::move(s)}, multiply{multiply} {}
   float getStat() const override
   {
      return next->getStat() * multiply;
   }
};