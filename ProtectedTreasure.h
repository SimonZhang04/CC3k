#include "WalkEffectObject.h"

class ProtectedTreasure : public WalkEffectObject
{
   virtual void unlockedEffect() = 0;

protected:
   bool isLocked = true;

public:
   void unlock() { isLocked = false; }
};