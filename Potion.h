#include "EffectObject.h"
#include <functional>

class Potion : public EffectObject
{
protected:
   Player &player;

public:
   Potion(Player &p) : player{p} {}
   static const char CHAR = 'P';
   char getChar() const override { return CHAR; };
   void consumePotion()
   {
      notifyObservers();
      useEffect();
   };
};