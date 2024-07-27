#include "Merchant.h"

bool Merchant::shouldAttack(Tile &playerTile)
{
   // Check if playerTile is in any neighbor tiles of the enemy
   if (isAggro)
   {
      return Enemy::shouldAttack(playerTile);
   }
};

// drop merchant horde
void Merchant::onDeath() {
};

int Merchant::receiveAttack(int attackerAtk)
{
   isAggro = true;
   return Enemy::receiveAttack(attackerAtk);
}

bool Merchant::isAggro = false;