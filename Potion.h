#include "EffectObject.h"
#include "PotionType.h"
#include <functional>

class Potion : public EffectObject
{
   PotionType type;
   std::function<void(PotionType)> onUse;

public:
   Potion(std::function<void(PotionType)> func, PotionType type) : onUse{func}, type{type} {}
   static const char CHAR = 'P';
   char getChar() const override { return CHAR; };

   // implement later
   void consumePotion() {};

protected:
   void useEffect() override
   {
      onUse(type);
   };
};