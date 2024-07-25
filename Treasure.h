#include "WalkEffectObject.h"
#include <functional>

class Treasure : public WalkEffectObject
{
   int gold;
   std::function<void(int)> onUse;

public:
   Treasure(std::function<void(int)> func) : onUse(func) {}
   Treasure(int g, std::function<void(int)> func) : gold(g), onUse(func) {}
   static const char CHAR = 'G';
   char getChar() const override { return CHAR; };

protected:
   void useEffect() override
   {
      onUse(gold);
   };
};