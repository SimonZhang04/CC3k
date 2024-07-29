#include "ProtectedTreasure.h"
#include "Treasure.h"
#include <functional>
#include <iostream>
class DragonHoard : public virtual ProtectedTreasure, public virtual Treasure
{
   std::function<float(int)> onUse;
   void unlockedEffect() { Treasure::useEffect(); };

public:
   DragonHoard(TreasureType treasureType, std::function<float(int)> func) : ProtectedTreasure{}, Treasure{treasureType, func}
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
