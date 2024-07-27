#include "Player.h"
#include "StatIncrementer.h"
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

void Player::useAttack(Character &c)
{
   std::cout << "Player attack: " << calculateAttack();
   c.receiveAttack(calculateAttack());
}

int Player::getGold() const
{
   return gold;
}

int Player::calculateAttack() const
{
   return modifiedAttack->getStat();
};

int Player::getAttack() const
{
   return calculateAttack();
};

int Player::getDefense() const
{
   return modifiedDefense->getStat();
};

void Player::onDeath()
{
}

void Player::useStatPotion(StatType type, int amount)
{
   modifyStat(type, amount);
}

void Player::modifyStat(StatType type, int amount)
{
   switch (type)
   {
   case StatType::Attack:
   {
      std::unique_ptr<Stat> newInc = std::make_unique<StatIncrementer>(amount, modifiedAttack);
      modifiedAttack = std::move(newInc);
      break;
   }
   case StatType::Defense:
   {
      std::unique_ptr<Stat> newInc = std::make_unique<StatIncrementer>(amount, modifiedDefense);
      modifiedDefense = std::move(newInc);
   }
   break;
   case StatType::Health:
      hp += amount;
      break;
   }
}
