#include "WalkEffectObject.h"
#include <functional>

class Stairway : public WalkEffectObject
{

   std::function<void()> onUse;
   bool isRevealed = false;

public:
   Stairway(std::function<void()> func) : onUse{func} {}
   static const char CHAR = '\\';
   static const char HIDDEN_CHAR = ' ';

   char getChar() const override
   {
      if (isRevealed)
         return CHAR;
      else
         return HIDDEN_CHAR;
   }
   // reveal is called by game logic
   void reveal() { isRevealed = true; };

protected:
   void useEffect() override
   {
      onUse();
   };
};