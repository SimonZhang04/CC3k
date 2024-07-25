#include "Enemy.h"

class Phoenix : public Enemy
{
   static const int BASE_HP = 50;
   static const int BASE_ATK = 35;
   static const int BASE_DEF = 20;

public:
   Phoenix(std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'X';
};