#ifndef SUBJECT
#define SUBJECT

#include "Observer.h"
#include <vector>

class Subject
{
   vector<Observer *> observers;

public:
   void atttach(Observer *o)
   {
      observers.emplace_back(o);
   }

   void detach(Observer *o)
   {
      observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
   }

   virtual ~Subject() = default;
};

#endif