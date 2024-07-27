#include "ProtectedTreasure.h"
#include "Treasure.h"
#include <functional>
#include <iostream>
class DragonHoard : public virtual ProtectedTreasure, public virtual Treasure
{
   std::function<void(int)> onUse;
   void unlockedEffect() { Treasure::useEffect(); };

public:
   DragonHoard(TreasureType treasureType, std::function<void(int)> func) : Treasure{treasureType, func}, ProtectedTreasure{}
   {
   }

protected:
   void useEffect() override
   {
      if (!isLocked)
      {
         unlockedEffect();
      }
   };
};