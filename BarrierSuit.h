#include "ProtectedTreasure.h"
#include <functional>

class BarrierSuit : public ProtectedTreasure
{

   std::function<void()> onUse;
   void unlockedEffect()
   {
      onUse();
      notifyObservers();
   };

public:
   BarrierSuit(std::function<void()> func) : ProtectedTreasure{}, onUse{func} {}
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