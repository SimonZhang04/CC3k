#include "Enemy.h"

// check for attack condition using player and player tile
bool Enemy::shouldAttack(Player &p, Tile &playerTile)
{
   if (p.occupyingTile)
};

bool Enemy::shouldMove()
{
   return true;
};

Tile Enemy::determineMoveTile() {

};

void Enemy::act(Player &p, Tile &playerTile)
{
   if (shouldAttack(p))
   {
      // attack
      attack(p);
   }
   else if (shouldMove())
   {
      // move
   }
};

// drop 1 gold, make sure to check if the enemy holds a compass, notify
void Enemy::onDeath(Player &p)
{
   p.collectGold(1);
}

int Enemy::calculateAttack()
{
   return baseAtk;
};
