#include "Enemy.h"

class Phoenix : public Enemy
{
   const int BASE_HP = 50;
   const int BASE_ATK = 35;
   const int BASE_DEF = 20;

public:
   Phoenix::Phoenix() : Enemy(BASE_HP, BASE_ATK, BASE_DEF) {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'X';
};