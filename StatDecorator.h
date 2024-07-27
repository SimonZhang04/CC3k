#ifndef STATDECORATOR
#define STATDECORATOR

#include "Stat.h"
#include <memory>

class StatDecorator : public Stat
{
protected:
   std::unique_ptr<Stat> next;

public:
   StatDecorator(std::unique_ptr<Stat> s) : next{std::move(s)} {}
   virtual ~StatDecorator() = default;
};

#endif