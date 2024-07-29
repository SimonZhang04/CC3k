#ifndef CHARACTER
#define CHARACTER

#include "Entity.h"
#include "Tile.h"

class Enemy;
class Player;

class Character : public Entity
{
   virtual void onDeath(Character &attacker) = 0;

protected:
   // virtual void onDeath() = 0;
   // virtual void attack(Character &c) = 0;

   Character(int maxHp, int baseAtk, int baseDef) : hp{maxHp}, maxHp{maxHp}, baseAtk{baseAtk}, baseDef{baseDef} {};
   virtual int calculateAttack() const = 0;

public:
   int hp, maxHp, baseAtk, baseDef;
   virtual int calculateDamageTaken(int attackerAtk);
   void receiveAttack(int damageTaken, Character &attacker);
   virtual void onReceiveAttack();
   virtual std::unique_ptr<Drawable> drawableToReplace() override { return nullptr; }
   virtual void didKill(Enemy *e) = 0;
   virtual void didKill(Player *p) = 0;
};

#endif