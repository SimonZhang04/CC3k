#ifndef SUBJECT
#define SUBJECT

#include "Observer.h"
#include <algorithm>
#include <string>
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

   void notifyDeathObservers()
   {
      for (auto p : observers)
      {
         p->notifyDeath(*this);
      }
   }

   void notifyActionObservers(std::string action)
   {
      for (auto p : observers)
      {
         p->notifyAction(action);
      }
   }

   virtual ~Subject() = default;
};

#endif