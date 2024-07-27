#include "Dragon.h"
bool Dragon::shouldMove()
{
   return false;
};

// update later
bool Dragon::shouldAttack(Tile &playerTile)
{
   int rDiff = abs(playerTile.getRow() - protectedTreasureRow);
   int cDiff = abs(playerTile.getCol() - protectedTreasureCol);

   return rDiff <= 1 && cDiff <= 1;
}

// update later
void Dragon::onDeath()
{
   protectedTreasure->unlock();
};