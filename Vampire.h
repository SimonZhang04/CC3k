#include "Enemy.h"

class Vampire : public Enemy
{
   const int BASE_HP = 50;
   const int BASE_ATK = 25;
   const int BASE_DEF = 25;

public:
   Vampire(std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'V';
};