#include "ProtectedTreasure.h"
#include "Treasure.h"
#include <functional>

class DragonHoard : public ProtectedTreasure, public Treasure
{
   int gold = 6;
   std::function<void(int)> onUse;
   void unlockedEffect() { onUse(gold); };

public:
   DragonHoard(std::function<void(int)> func) : Treasure{func} {}

protected:
   void useEffect() override
   {
      if (!isLocked)
      {
         unlockedEffect();
      }
   };
};