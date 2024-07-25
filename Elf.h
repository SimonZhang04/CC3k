#include "Player.h"
#include "StatViewer.h"

class Elf : public Player
{
   static const int BASE_HP = 50;
   static const int BASE_ATK = 25;
   static const int BASE_DEF = 25;
   static const float SCORE_MODIFIER = 1;
   static const float GOLD_MODIFIER = 1;

public:
   Elf() : Player{BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER, "Elf"} {}
   virtual void usePotion(PotionType, int amount) override;
};
