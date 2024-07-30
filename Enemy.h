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
   int deathGold;

protected:
   Enemy(int maxHp, int baseAtk, int baseDef, Tile *occupyingTile, std::unique_ptr<Drawable> loot, int deathGold = 1) : Character{maxHp, baseAtk, baseDef}, occupyingTile{occupyingTile}, loot{std::move(loot)}, deathGold{deathGold} {};
   virtual int calculateAttack() const override;
   virtual int calculateDefense() const override;
   virtual bool shouldMove();
   virtual bool shouldAttack(Tile &playerTile);
   void onDeath(Character &attacker) override;

public:
   std::string act(Player &p, Tile &playerTile);
   virtual std::unique_ptr<Drawable> drawableToReplace() override { return std::move(loot); };
   int getHp() const;
   int getDeathRewardGold() { return deathGold; };
   void didKill(Player *p) override;
   void didKill(Enemy *e) override;
};

#endif
