#ifndef TREASURE
#define TREASURE

#include "TreasureType.h"
#include "WalkEffectObject.h"
#include <functional>

class Treasure : public virtual WalkEffectObject
{
   int gold;
   std::function<void(int)> onUse;
   static const std::map<TreasureType, int> GOLD_MAP;

protected:
   void useEffect() override
   {
      onUse(gold);
      notifyObservers();
   };

public:
   Treasure(TreasureType t, std::function<void(int)> func) : gold(GOLD_MAP.at(t)), onUse(func) {}
   static const char CHAR = 'G';
   char getChar() const override { return CHAR; };
};

const std::map<TreasureType, int> Treasure::GOLD_MAP = {{TreasureType::NormalTreasure, 1}, {TreasureType::SmallHoard, 2}, {TreasureType::MerchantsHoard, 4}, {TreasureType::DragonHoard, 6}};

#endif
