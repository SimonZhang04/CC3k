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
   void useEffect() override
   {
      if (!isLocked)
      {
         unlockedEffect();
      }
   };

public:
   void unlock()
   {
      isLocked = false;
   }
};

#endif
