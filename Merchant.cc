#include "Merchant.h"

bool Merchant::shouldAttack(Tile &playerTile)
{
   // Check if playerTile is in any neighbor tiles of the enemy
   if (isAggro)
   {
      return Enemy::shouldAttack(playerTile);
   }
};

void Merchant::onReceiveAttack()
{
   isAggro = true;
}

bool Merchant::isAggro = false;