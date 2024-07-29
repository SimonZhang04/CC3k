#include "Enemy.h"
#include <iostream>
#include <random>
#include <string>

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
      int coinflip = rand() % 2;
      if (coinflip == 1)
      {
         int damageDone = p.calculateDamageTaken(calculateAttack());
         p.receiveAttack(damageDone, *this);
         return (std::string(1, getChar()) + " deals " + std::to_string(damageDone) + " damage to PC.");
      }
      else
      {
         return (std::string(1, getChar()) + " missed attack on PC.");
      }
   }
   else if (shouldMove())
   {
      Tile &moveTile = determineMoveTile();
      occupyingTile->moveTo(moveTile);
      occupyingTile = &moveTile;
   }
   return "";
};

void Enemy::didKill(Player *p) {
};

void Enemy::didKill(Enemy *e) {
};

void Enemy::onDeath(Character &attacker)
{
   attacker.didKill(this);
}

int Enemy::calculateAttack() const
{
   return baseAtk;
};

int Enemy::getHp() const
{
   return hp;
}