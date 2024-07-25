#include "Player.h"
#include "StatViewer.h"

class Dwarf : public Player
{
   const int BASE_HP = 100;
   const int BASE_ATK = 20;
   const int BASE_DEF = 30;
   const int SCORE_MODIFIER = 1;
   const int GOLD_MODIFIER = 2;

public:
   Dwarf() : Player(BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER) {}
};
