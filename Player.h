#include "Character.h"
#include "PotionType.h"
#include "Stat.h"
#include <memory>

class Player : public Character
{

   void useAttack(Character &c);

protected:
   int gold;
   float scoreModifier;
   float goldModifier;
   Player(int maxHp, int baseAtk, int baseDef)
       : Character(maxHp, baseAtk, baseDef), // Initialize base class with parameters
         gold(0), scoreModifier(0.0f), goldModifier(0.0f)
   {
   }

public:
   std::unique_ptr<Stat> modifiedAttack;
   std::unique_ptr<Stat> modifiedDefense;

   virtual int collectGold();
   char getChar() const override;
   int getScore();
   virtual void usePotion(PotionType);
};