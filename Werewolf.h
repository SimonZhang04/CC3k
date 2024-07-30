#include "Enemy.h"

class Werewolf : public Enemy
{
   static const int BASE_HP = 120;
   static const int BASE_ATK = 30;
   static const int BASE_DEF = 5;

public:
   Werewolf(bool bonusActive, Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{bonusActive, BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'W';
};
