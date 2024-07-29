#include "EffectObject.h"
#include "PotionType.h"
#include <functional>

class Potion : public EffectObject
{
protected:
   Player &player;
   PotionType type;

public:
   Potion(Player &p, PotionType type) : player{p}, type{type} {}
   std::string getPotionType() const
   {
      switch (type)
      {
      case PotionType::RestoreHealth:
         return "RH";
      case PotionType::BoostAtk:
         return "BA";
      case PotionType::BoostDef:
         return "BD";
      case PotionType::PoisonHealth:
         return "PH";
      case PotionType::WoundAtk:
         return "WA";
      case PotionType::WoundDef:
         return "WD";
      }
      return "";
   }
   static const char CHAR = 'P';
   char getChar() const override { return CHAR; };
   void consumePotion()
   {
      useEffect();
      notifyActionObservers("uses " + getPotionType());
      notifyDeathObservers();
   };
};
