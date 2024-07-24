#include "Entity.h"

class Character : public Entity
{
   virtual void onDeath() = 0;
   virtual void attack(Character &c) = 0;

public:
   int hp, maxHp, baseDef, baseAtk;
   virtual void recieveAttack(int dmg);
};