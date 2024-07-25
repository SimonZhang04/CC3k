#include "Enemy.h"
#include <random>

bool Enemy::shouldAttack(Tile &playerTile)
{
   // Check if playerTile is in any neighbor tiles of the enemy
   for (Tile *neighbor : occupyingTile->getValidNeighbors())
   {
      if (neighbor == &playerTile)
      {
         return true;
      }
   }
   return false;
}

bool Enemy::shouldMove()
{
   return true;
};

Tile &Enemy::determineMoveTile()
{
   std::vector<Tile *> validNeighbors = occupyingTile->getValidNeighbors();

   if (validNeighbors.empty())
   {
      return *occupyingTile;
   }

   int idx = rand() % validNeighbors.size();
   Tile *selectedTile = validNeighbors[idx];

   return *selectedTile;
}

void Enemy::act(Player &p, Tile &playerTile)
{
   if (shouldAttack(playerTile))
   {
      // attack
      p.recieveAttack(calculateAttack());
   }
   else if (shouldMove())
   {
      Tile &moveTile = determineMoveTile();
      occupyingTile->moveTo(moveTile);
      occupyingTile = &moveTile;
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
