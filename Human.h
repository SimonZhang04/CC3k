#include "Player.h"

class Human : public Player
{
   static const int BASE_HP = 140;
   static const int BASE_ATK = 20;
   static const int BASE_DEF = 20;
   static constexpr float SCORE_MODIFIER = 1.5;
   static constexpr float GOLD_MODIFIER = 1;

public:
   Human() : Player(BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER, "Human") {}
};
