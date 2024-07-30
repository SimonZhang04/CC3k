#include "Enemy.h"

class Vampire : public Enemy
{
   static const int BASE_HP = 50;
   static const int BASE_ATK = 25;
   static const int BASE_DEF = 25;

protected:
   std::string onAttack(Player &target, int damageDealt) override
   {
      if (bonusActive)
      {
         int amt = healHp(damageDealt);
         return amt > 0 ? " heals " + std::to_string(amt) + " HP (" + std::to_string(hp) + ")" : "";
      }
      return "";
   };

public:
   Vampire(bool bonusActive, Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{bonusActive, BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'V';
};
