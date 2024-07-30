#include "Enemy.h"
#include "StringFormatter.h"

class Goblin : public Enemy
{
   static const int BASE_HP = 70;
   static const int BASE_ATK = 5;
   static const int BASE_DEF = 10;
   const int goldStolen = 0.5f;

public:
   std::string onAttack(Player &target, int damageDealt) override
   {
      if (bonusActive)
      {
         float goldLost = target.loseGold(0.5f);
         deathGold += goldLost;
         return goldLost > 0 ? " steals " + StringFormatter::formatFloat(goldLost) + " gold" : "";
      }
      return "";
   };
   Goblin(bool bonusActive, Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{bonusActive, BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'N';
};
