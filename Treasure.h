#ifndef TREASURECLASS
#define TREASURECLASS

#include "TreasureType.h"
#include "WalkEffectObject.h"
#include <functional>
#include <map>
#include <string>

class Treasure : public virtual WalkEffectObject
{
   int gold;
   std::function<void(int)> onUse;
   static const std::map<TreasureType, int> GOLD_MAP;

protected:
   void useEffect() override
   {
      onUse(gold);
      notifyActionObservers(std::to_string(gold) + " gold picked up!");
      notifyDeathObservers();
   };

public:
   Treasure(TreasureType t, std::function<void(int)> func) : gold(GOLD_MAP.at(t)), onUse(func) {}
   static const char CHAR = 'G';
   char getChar() const override { return CHAR; };
};

#endif
