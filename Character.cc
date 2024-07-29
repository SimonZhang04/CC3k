#include "Character.h"
#include <cmath>
#include <iostream>

int Character::calculateDamageTaken(int attackerAtk)
{
   int takenDamage = std::ceil(100.0 / (100.0 + baseDef)) * attackerAtk;
   return takenDamage;
}

void Character::receiveAttack(int damageTaken)
{
   hp -= damageTaken;
   onReceiveAttack();
   if (hp <= 0)
   {
      onDeath();
      notifyDeathObservers();
   }
}

void Character::onReceiveAttack()
{
}