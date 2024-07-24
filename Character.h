#include "Entity.h"

class Character : public Entity
{
protected:
   virtual void onDeath() = 0;
   virtual void attack(Character &c) = 0;
   Character(int maxHp, int baseAtk, int baseDef) : maxHp{maxHp}, baseAtk{baseAtk}, baseDef{baseDef}, hp{maxHp} {};

public:
   int hp, maxHp, baseAtk, baseDef;
   virtual void recieveAttack(int dmg);
};