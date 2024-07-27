#ifndef SUBJECT
#define SUBJECT

#include "Observer.h"
#include <algorithm>
#include <vector>

class Subject
{
   std::vector<Observer *> observers;

public:
   void attach(Observer *o)
   {
      observers.emplace_back(o);
   }

   void detach(Observer *o)
   {
      observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
   }

   void notifyObservers()
   {
      for (auto p : observers)
      {
         p->notify(*this);
      }
   }

   virtual ~Subject() = default;
};

#endif