#include "Player.h"

void Player::collectGold(int goldPickedUp)
{
   gold += goldPickedUp * goldModifier;
};

char Player::getChar() const
{
   return '@';
};

int Player::getScore() const
{
   return gold * scoreModifier;
};

// implement later
void Player::usePotion(PotionType){

};

void Player::useAttack(Character &c)
{
   c.recieveAttack(modifiedAttack->getStat());
}