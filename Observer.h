#ifndef SUBJECT
#define SUBJECT

class Observer
{
public:
   virtual void notify() = 0;
   virtual ~Observer() {};
};

#endif