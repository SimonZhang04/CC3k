#include "Player.h"

class Human : public Player
{
   const int BASE_HP = 140;
   const int BASE_ATK = 20;
   const int BASE_DEF = 20;
   const int SCORE_MODIFIER = 1.5;
   const int GOLD_MODIFIER = 1;

public:
   Human::Human() : Player(BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER) {}
};
