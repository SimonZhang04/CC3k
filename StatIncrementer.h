#include "StatDecorator.h"

class StatIncrementer : public StatDecorator
{
   int increment;

public:
   StatIncrementer(const int increment, std::unique_ptr<Stat> s) : StatDecorator{std::move(s)}, increment{increment} {}
   int getStat() const override;
};