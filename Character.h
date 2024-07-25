#include "Entity.h"
#include "Tile.h"

class Character : public Entity
{
protected:
   virtual void onDeath() = 0;
   virtual void attack(Character &c) = 0;
   Tile *occupyingTile;
   Character(int maxHp, int baseAtk, int baseDef) : maxHp{maxHp}, baseAtk{baseAtk}, baseDef{baseDef}, hp{maxHp} {};
   virtual int calculateAttack() = 0;

public:
   int hp, maxHp, baseAtk, baseDef;
   virtual void recieveAttack(int dmg);
};