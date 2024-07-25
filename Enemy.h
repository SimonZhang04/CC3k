#ifndef ENEMY
#define ENEMY

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
   virtual bool shouldMove();
   Tile &determineMoveTile();
   Tile *occupyingTile;
   std::unique_ptr<Drawable> loot = nullptr;

protected:
   Enemy(int maxHp, int baseAtk, int baseDef, std::unique_ptr<Drawable> loot) : Character{maxHp, baseAtk, baseDef}, loot{std::move(loot)} {};
   virtual int calculateAttack() override;
   virtual bool shouldAttack(Tile &playerTile);

public:
   std::string act(Player &p, Tile &playerTile);
   virtual void onDeath(Player &p);
   virtual std::unique_ptr<Drawable> drawableToReplace() override { return std::move(loot); };
};

#endif
