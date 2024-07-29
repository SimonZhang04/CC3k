#include "Player.h"
#include "StatViewer.h"

class Elf : public Player
{
   static const int BASE_HP = 50;
   static const int BASE_ATK = 25;
   static const int BASE_DEF = 25;
   static constexpr float SCORE_MODIFIER = 1;
   static constexpr float GOLD_MODIFIER = 1;

public:
   Elf() : Player{BASE_HP, BASE_ATK, BASE_DEF, SCORE_MODIFIER, GOLD_MODIFIER, PlayerRace::Elf} {}
   virtual void useStatPotion(StatType type, int amount) override;
};
