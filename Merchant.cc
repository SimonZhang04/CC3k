#include "Merchant.h"

bool Merchant::shouldAttack(Tile &playerTile)
{
   // Check if playerTile is in any neighbor tiles of the enemy
   if (isAggro)
   {
      return Enemy::shouldAttack(playerTile);
   }
};

// drop merchant horde and set to aggro if it isn't
void Merchant::onDeath(Player &p)
{
   if (!isAggro)
   {
      isAggro = true;
   }
   p.collectGold(4);
};

bool Merchant::isAggro = false;