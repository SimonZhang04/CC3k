#ifndef OBSERVER
#define OBSERVER

class Subject;

class Observer
{
public:
   virtual void notify(Subject &entity) = 0;
   virtual ~Observer() {};
};

#endif