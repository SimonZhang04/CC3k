#ifndef OBSERVER
#define OBSERVER
#include <string>
class Subject;

class Observer
{
public:
   virtual void notifyDeath(Subject &entity) = 0;
   virtual void notifyAction(std::string &action) = 0;
   virtual ~Observer() {};
};

#endif
