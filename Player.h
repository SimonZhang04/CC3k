#include "Character.h"
#include "PotionType.h"
#include "Stat.h"
#include "StatViewer.h"
#include <memory>

class Player : public Character
{
   void useAttack(Character &c);

protected:
   int gold;
   float scoreModifier;
   float goldModifier;
   Player(int maxHp, int baseAtk, int baseDef, float scoreModifer, float goldModifer)
       : Character{maxHp, baseAtk, baseDef},
         gold{0}, scoreModifier{scoreModifer}, goldModifier{goldModifer}
   {
      modifiedAttack = std::make_unique<StatViewer>(baseAtk);
      modifiedDefense = std::make_unique<StatViewer>(baseDef);
   };

public:
   std::unique_ptr<Stat> modifiedAttack;
   std::unique_ptr<Stat> modifiedDefense;

   void collectGold(int goldPickedUp);
   char getChar() const override;
   int getScore() const;
   virtual void usePotion(PotionType, int amount);
};