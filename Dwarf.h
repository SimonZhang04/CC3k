#include "Player.h"
#include "StatViewer.h"

class Dwarf : public Player
{
   static const int BASE_HP = 100;
   static const int BASE_ATK = 20;
   static const int BASE_DEF = 30;
   static constexpr float SCORE_MODIFIER = 1;
   static constexpr float GOLD_MODIFIER = 2;

public:
   Dwarf() : Player(BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER, "Dwarf") {}
};
