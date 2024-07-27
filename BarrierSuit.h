#include "ProtectedTreasure.h"
#include "StatType.h"
#include <functional>

class BarrierSuit : public ProtectedTreasure
{

   std::function<void(StatType, float)> onUse;

   void unlockedEffect()
   {
      StatType stat = StatType::ReceivedDamageMultiplier;
      float value = 0.5;
      onUse(stat, value);
      notifyObservers();
   };

public:
   BarrierSuit(std::function<void(StatType, float)> func) : ProtectedTreasure{}, onUse{func} {}
   static const char CHAR = 'B';
   char getChar() const override { return CHAR; };

protected:
   void useEffect() override
   {
      if (!isLocked)
      {
         unlockedEffect();
      }
   };
};