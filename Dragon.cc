#include "Dragon.h"
bool Dragon::shouldMove()
{
   return false;
};

bool Dragon::shouldAttack(Tile &playerTile)
{
   int rDiff = abs(playerTile.getRow() - protectedTreasureRow);
   int cDiff = abs(playerTile.getCol() - protectedTreasureCol);

   return (rDiff <= 1 && cDiff <= 1) || Enemy::shouldAttack(playerTile);
}

void Dragon::onDeath(Character &attacker)
{
   Enemy::onDeath(attacker);
   protectedTreasure->unlock();
};
