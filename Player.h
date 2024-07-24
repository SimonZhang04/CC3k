#include "Character.h"
#include "PotionType.h"
#include "Stat.h"

class Player : public Character
{
   int gold;
   float scoreModifier;
   float goldModifier;
   void useAttack(Character &c);

public:
   Stat *modifiedAttack;
   Stat *modifiedDefense;
   virtual int collectGold();
   char getChar() const override;
   int getScore();
   virtual void usePotion(PotionType);
};