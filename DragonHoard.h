#include "ProtectedTreasure.h"
#include "Treasure.h"
#include <functional>
#include <iostream>
class DragonHoard : public virtual ProtectedTreasure, public virtual Treasure
{
   void unlockedEffect() { Treasure::useEffect(); };

public:
   DragonHoard(TreasureType treasureType, std::function<float(int)> func) : ProtectedTreasure{}, Treasure{treasureType, func}
   {
   }

protected:
   void useEffect() override
   {
      ProtectedTreasure::useEffect();
   }
};
