#include "Enemy.h"

class Troll : public Enemy
{
   static const int BASE_HP = 120;
   static const int BASE_ATK = 25;
   static const int BASE_DEF = 15;

public:
   Troll(Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'T';
};
