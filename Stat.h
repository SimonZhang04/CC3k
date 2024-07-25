#ifndef STAT
#define STAT

class Stat
{
public:
   virtual int getStat() const = 0;
   virtual ~Stat() {};
};

#endif