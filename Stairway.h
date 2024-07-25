#include "WalkEffectObject.h"
#include <functional>

class Stairway : public WalkEffectObject
{

   std::function<void()> onUse;
   bool isRevealed = false;

public:
   Stairway(std::function<void()> func) : onUse{func} {}
   char getChar() const override
   {
      if (isRevealed)
         return '\\';
      else
         return ' ';
   }
   // reveal is called by game logic
   void reveal() { isRevealed = true; };

protected:
   void useEffect() override
   {
      onUse();
   };
};