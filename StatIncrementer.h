#include "StatDecorator.h"
#include <memory>

class StatIncrementer : public StatDecorator
{
   float increment;

public:
   StatIncrementer(const float increment, std::unique_ptr<Stat> s) : StatDecorator{std::move(s)}, increment{increment} {}
   float getStat() const override;
};