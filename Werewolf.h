#include "Enemy.h"

class Werewolf : public Enemy
{
   const int BASE_HP = 120;
   const int BASE_ATK = 30;
   const int BASE_DEF = 5;

public:
   Werewolf::Werewolf() : Enemy(BASE_HP, BASE_ATK, BASE_DEF) {};
   char getChar() const override { return 'W'; };
};