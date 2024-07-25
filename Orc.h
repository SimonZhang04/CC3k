#include "Player.h"
#include "StatViewer.h"

class Orc : public Player
{
   static const int BASE_HP = 180;
   static const int BASE_ATK = 30;
   static const int BASE_DEF = 25;
   static const float SCORE_MODIFIER = 1;
   static const float GOLD_MODIFIER = 0.5;

public:
   Orc() : Player(BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER, "Orc") {}
};
