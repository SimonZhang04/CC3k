#include "Player.h"
#include "StatViewer.h"

class Elf : public Player
{
public:
   Elf::Elf() : Player(140, 30, 10, 1, 1) {}
   virtual void usePotion(PotionType) override;
};
