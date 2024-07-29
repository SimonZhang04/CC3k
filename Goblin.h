#include "Enemy.h"

class Goblin : public Enemy
{
   static const int BASE_HP = 70;
   static const int BASE_ATK = 5;
   static const int BASE_DEF = 10;

public:
   Goblin(Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'N';
};
