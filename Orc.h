#include "Player.h"
#include "StatViewer.h"

class Orc : public Player
{
   const int BASE_HP = 180;
   const int BASE_ATK = 30;
   const int BASE_DEF = 25;
   const int SCORE_MODIFIER = 1;
   const int GOLD_MODIFIER = 0.5;

public:
   Orc::Orc() : Player(BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER) {}
};
