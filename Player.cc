#include "Player.h"
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

// implement later
void Player::usePotion(PotionType, int amount) {

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
