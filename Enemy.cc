#include "Enemy.h"
#include <random>
#include <string>
#include <iostream>

bool Enemy::shouldAttack(Tile &playerTile)
{
   // Check if playerTile is in within 1 tile of enemy
   int cdiff = abs(occupyingTile->getCol() - playerTile.getCol());
   int rdiff = abs(occupyingTile->getRow() - playerTile.getRow());
   return cdiff <= 1 && rdiff <= 1;
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

std::string Enemy::act(Player &p, Tile &playerTile)
{
   if (shouldAttack(playerTile))
   {
      // attack
      int damageDone = p.receiveAttack(calculateAttack());
      return getChar() + " deals " + std::to_string(damageDone) + " damage to PC";
   }
   else if (shouldMove())
   {
      Tile &moveTile = determineMoveTile();
      occupyingTile->moveTo(moveTile);
      occupyingTile = &moveTile;
   }
   return "";
};

// drop 1 gold, make sure to check if the enemy holds a compass, notify
void Enemy::onDeath(Player &p)
{
   p.collectGold(1);
}

int Enemy::calculateAttack() const
{
   return baseAtk;
};
