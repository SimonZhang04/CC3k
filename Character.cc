#include "Character.h"
#include <cmath>

int Character::recieveAttack(int attackerAtk)
{
   int takenDamage = std::ceil(100 / (100 + baseDef)) * attackerAtk;
   hp -= takenDamage;
   return takenDamage;
}
