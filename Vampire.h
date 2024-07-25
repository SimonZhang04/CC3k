#include "Enemy.h"

class Vampire : public Enemy
{
   static const int BASE_HP = 50;
   static const int BASE_ATK = 25;
   static const int BASE_DEF = 25;

public:
   Vampire(Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'V';
};