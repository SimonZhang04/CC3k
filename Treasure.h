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
   std::function<float(int)> onUse;
   static const std::map<TreasureType, int> GOLD_MAP;

protected:
   void useEffect() override;

public:
   Treasure(TreasureType t, std::function<float(int)> func) : gold(GOLD_MAP.at(t)), onUse(func) {}
   static const char CHAR = 'G';
   char getChar() const override { return CHAR; };
};

#endif
