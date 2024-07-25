#ifndef CHARCTER
#define CHARCTER

#include "Entity.h"
#include "Tile.h"

class Character : public Entity
{
protected:
   // virtual void onDeath() = 0;
   // virtual void attack(Character &c) = 0;

   Character(int maxHp, int baseAtk, int baseDef) : hp{maxHp}, maxHp{maxHp}, baseAtk{baseAtk}, baseDef{baseDef} {};
   virtual int calculateAttack() = 0;

public:
   int hp, maxHp, baseAtk, baseDef;
   virtual void recieveAttack(int attackerAtk);
   virtual std::unique_ptr<Drawable> drawableToReplace() override { return nullptr; }
};

#endif