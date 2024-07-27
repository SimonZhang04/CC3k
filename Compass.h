#include "WalkEffectObject.h"
#include <functional>
#include <iostream>

class Compass : public WalkEffectObject
{

   std::function<void()> onUse;

public:
   Compass(std::function<void()> func) : onUse{func} {}
   static const char CHAR = 'C';
   char getChar() const override { return CHAR; };

protected:
   void useEffect() override
   {
      std::cout << "COMPASS EFFECT" << std::endl;
      onUse();
   };
};