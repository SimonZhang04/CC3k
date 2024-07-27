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
   void onDeath() override;

protected:
   Enemy(int maxHp, int baseAtk, int baseDef, Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Character{maxHp, baseAtk, baseDef}, occupyingTile{occupyingTile}, loot{std::move(loot)} {};
   virtual int calculateAttack() const override;
   virtual bool shouldAttack(Tile &playerTile);

public:
   std::string act(Player &p, Tile &playerTile);
   virtual std::unique_ptr<Drawable> drawableToReplace() override { return std::move(loot); };
};

#endif
