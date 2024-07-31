#ifndef ENEMY
#define ENEMY

#include "Character.h"
#include "Player.h"
#include <iostream>

class Enemy : public Character
{
   Tile &determineMoveTile();
   Tile *occupyingTile;
   std::unique_ptr<Drawable> loot = nullptr;
   void appendAction(std::string &oldAction, std::string &&newAction);

protected:
   Enemy(bool bonusActive, int maxHp, int baseAtk, int baseDef, Tile *occupyingTile, std::unique_ptr<Drawable> loot, int deathGold = 1)
       : Character{maxHp, baseAtk, baseDef},
         occupyingTile{occupyingTile},
         loot{std::move(loot)},
         bonusActive{bonusActive},
         deathGold{static_cast<float>(deathGold)} {};
   bool bonusActive;
   float deathGold;
   virtual int calculateAttack() const override;
   virtual int calculateDefense() const override;
   virtual bool shouldMove();
   virtual bool shouldAttack(Tile &playerTile);
   virtual std::string onAttack(Player &target, int damageDealt);
   virtual std::string onAct() { return ""; };
   void onDeath(Character &attacker) override;

public:
   std::string act(Player &p, Tile &playerTile);
   virtual std::unique_ptr<Drawable> drawableToReplace() override { return std::move(loot); };
   int getHp() const;
   float getDeathRewardGold()
   {
      return deathGold;
   };
   void didKill(Player *p) override;
   void didKill(Enemy *e) override;
};

#endif
