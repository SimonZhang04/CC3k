#ifndef PROTECTEDTREASURE
#define PROTECTEDTREASURE

#include "WalkEffectObject.h"
#include <iostream>

class ProtectedTreasure : public virtual WalkEffectObject
{
   virtual void unlockedEffect() = 0;

protected:
   bool isLocked;
   ProtectedTreasure() : isLocked{true} {};

public:
   void unlock()
   {
      std::cout << "UNLOCK" << std::endl;
      isLocked = false;
   }
};

#endif
