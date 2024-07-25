#include "ProtectedTreasure.h"
#include <functional>

class BarrierSuit : public ProtectedTreasure
{

   std::function<void()> onUse;
   void unlockedEffect() { onUse(); };

public:
   BarrierSuit(std::function<void()> func) : onUse{func} {}
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