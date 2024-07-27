#include "Dragon.h"
bool Dragon::shouldMove()
{
   return false;
};

// update later
bool Dragon::shouldAttack(Tile &playerTile)
{
   return Enemy::shouldAttack(playerTile);
}

// update later
void Dragon::onDeath()
{
   protectedTreasure->unlock();
};