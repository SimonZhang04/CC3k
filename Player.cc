#include "Player.h"

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
   c.recieveAttack(modifiedAttack->getStat());
}