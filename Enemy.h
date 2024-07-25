#include "Character.h"
#include "Player.h"
#include "Tile.h"

class Enemy : public Character
{
   virtual bool shouldAttack(Player &p, Tile &playerTile);
   virtual bool shouldMove();
   Tile determineMoveTile();
   virtual int calculateAttack() override;

protected:
   Enemy(int maxHp, int baseAtk, int baseDef) : Character{maxHp, baseAtk, baseDef} {};

public:
   void act(Player &p, Tile &playerTile);
   virtual void onDeath(Player &p);
};