#include "Enemy.h"

class Goblin : public Enemy
{
   const int BASE_HP = 70;
   const int BASE_ATK = 5;
   const int BASE_DEF = 10;

public:
   Goblin::Goblin() : Enemy(BASE_HP, BASE_ATK, BASE_DEF) {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'N';
};