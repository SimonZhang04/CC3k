#ifndef PLAYER
#define PLAYER

#include "Character.h"
#include "PotionType.h"
#include "Stat.h"
#include "StatViewer.h"
#include <memory>
#include <string>

class Player : public Character
{
   std::unique_ptr<Stat> modifiedAttack;
   std::unique_ptr<Stat> modifiedDefense;

protected:
   int gold;
   float scoreModifier;
   float goldModifier;
   Player(int maxHp, int baseAtk, int baseDef, float scoreModifer, float goldModifer, std::string race)
       : Character{maxHp, baseAtk, baseDef},
         gold{0}, scoreModifier{scoreModifer}, goldModifier{goldModifer}, race{race}, modifiedAttack{std::make_unique<StatViewer>(this->baseAtk)}, modifiedDefense{std::make_unique<StatViewer>(this->baseDef)} {};
   virtual int calculateAttack() const;

public:
   static const char CHAR = '@';
   const std::string race;

   void collectGold(int goldPickedUp);
   char getChar() const override;
   int getScore() const;
   int getGold() const;
   int getAttack() const;
   int getDefense() const;
   void useAttack(Character &c);
   virtual void usePotion(PotionType, int amount);
};

#endif