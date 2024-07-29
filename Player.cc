#include "Player.h"
#include "Enemy.h"
#include "StatIncrementer.h"
#include "StatMultiplier.h"
#include <cmath>
#include <iostream>

void Player::collectGold(int goldPickedUp)
{
   gold += goldPickedUp * goldModifier;
};

char Player::getChar() const
{
   return CHAR;
};

int Player::getScore() const
{
   return gold * scoreModifier;
};

int Player::useAttack(Character &c)
{
   int damageDone = c.calculateDamageTaken(calculateAttack());
   c.receiveAttack(damageDone, *this);
   return damageDone;
}

void Player::didKill(Player *p) {
};

void Player::didKill(Enemy *e)
{
   int goldCollected = e->getDeathRewardGold();
   collectGold(goldCollected);
   notifyActionObservers("gained " + std::to_string(goldCollected) + " gold from killing enemy " + std::string(1, e->getChar()));
};

float Player::getGold() const
{
   return gold;
}

int Player::calculateAttack() const
{
   return static_cast<int>(modifiedAttack->getStat());
};

int Player::getAttack() const
{
   return calculateAttack();
};

int Player::getDefense() const
{
   return static_cast<int>(modifiedDefense->getStat());
};

int Player::calculateDamageTaken(int attackerAtk)
{
   int takenDamage = Character::calculateDamageTaken(attackerAtk) * receivedDamageMultiplier->getStat();
   return takenDamage;
}

void Player::onDeath(Character &attacker)
{
}

void Player::useStatPotion(StatType type, int amount)
{
   modifyStat(type, amount);
}

void Player::modifyStat(StatType type, float amount)
{
   switch (type)
   {
   case StatType::Attack:
   {
      std::unique_ptr<Stat> newInc = std::make_unique<StatIncrementer>(amount, std::move(modifiedAttack));

      modifiedAttack = std::move(newInc);
      break;
   }
   case StatType::Defense:
   {
      std::unique_ptr<Stat> newInc = std::make_unique<StatIncrementer>(amount, std::move(modifiedDefense));
      modifiedDefense = std::move(newInc);
      break;
   }
   case StatType::Health:
   {
      if (hp + amount > maxHp)
      {
         hp = maxHp;
      }
      else if (hp + amount < 0)
      {
         hp = 0;
      }
      else
      {
         hp += amount;
      }
      break;
   }
   case StatType::ReceivedDamageMultiplier:
   {
      std::unique_ptr<Stat> newMult = std::make_unique<StatMultiplier>(amount, std::move(receivedDamageMultiplier));
      receivedDamageMultiplier = std::move(newMult);
      break;
   }
   }
}

void Player::onFloorProgressed()
{
   std::unique_ptr<Stat> s = modifiedAttack->undecorate();
   while (s != nullptr)
   {
      modifiedAttack = std::move(s);
      s = modifiedAttack->undecorate();
   }

   s = modifiedDefense->undecorate();
   while (s != nullptr)
   {
      modifiedDefense = std::move(s);
      s = modifiedDefense->undecorate();
   }
}