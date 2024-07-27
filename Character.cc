#include "Character.h"
#include <cmath>
#include <iostream>

int Character::receiveAttack(int attackerAtk)
{
   int takenDamage = std::ceil(100.0 / (100.0 + baseDef)) * attackerAtk;
   hp -= takenDamage;
   if (hp <= 0)
   {
      onDeath();
      notifyObservers();
   }
   return takenDamage;
}
