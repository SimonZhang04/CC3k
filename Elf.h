#include "Player.h"
#include "StatViewer.h"

class Elf : public Player
{
   const int BASE_HP = 50;
   const int BASE_ATK = 25;
   const int BASE_DEF = 25;
   const int SCORE_MODIFIER = 1;
   const int GOLD_MODIFIER = 1;

public:
   Elf::Elf() : Player(BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER) {}
   virtual void usePotion(PotionType, int amount) override;
};
