#include "Enemy.h"

class Troll : public Enemy
{
   static const int BASE_HP = 120;
   static const int BASE_ATK = 25;
   static const int BASE_DEF = 15;
   const int healAmt = 5;

public:
   Troll(bool bonusActive, Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{bonusActive, BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   std::string onAct() override
   {
      if (bonusActive)
      {
         int amt = healHp(healAmt);
         return amt > 0 ? " heals " + std::to_string(amt) + " HP (" + std::to_string(hp) + ")" : "";
      }
      return "";
   };
   char getChar() const override { return CHAR; };
   static const char CHAR = 'T';
};
