#ifndef STAT
#define STAT
#include <memory>

class Stat
{
public:
   virtual float getStat() const = 0;
   virtual ~Stat() {};
   virtual std::unique_ptr<Stat> undecorate() = 0;
};

#endif