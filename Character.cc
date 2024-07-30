#include "Character.h"
#include <cmath>
#include <iostream>

int Character::calculateDamageTaken(int attackerAtk)
{
   int takenDamage = std::ceil(100.0 / (100.0 + calculateDefense())) * attackerAtk;
   return takenDamage;
}

void Character::receiveAttack(int damageTaken, Character &attacker)
{
   hp -= damageTaken;
   onReceiveAttack();
   if (hp <= 0)
   {
      onDeath(attacker);
      notifyDeathObservers();
   }
}

void Character::onReceiveAttack()
{
}

int Character::healHp(int amount)
{
   int actualHeal = std::min(maxHp - hp, amount);
   hp += actualHeal;
   return actualHeal;
}
