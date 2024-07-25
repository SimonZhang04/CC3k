#include "Character.h"
#include "Player.h"
#include "Tile.h"

class Enemy : public Character
{
   virtual bool shouldMove();
   Tile &determineMoveTile();
   virtual int calculateAttack() override;
   Tile *occupyingTile;

protected:
   Enemy(int maxHp, int baseAtk, int baseDef) : Character{maxHp, baseAtk, baseDef} {};
   virtual bool shouldAttack(Tile &playerTile);

public:
   void act(Player &p, Tile &playerTile);
   virtual void onDeath(Player &p);
};