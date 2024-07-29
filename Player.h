#ifndef PLAYER
#define PLAYER

#include "Character.h"
#include "PlayerRace.h"
#include "PotionType.h"
#include "Stat.h"
#include "StatType.h"
#include "StatViewer.h"
#include <memory>
#include <string>

class Player : public Character
{
   std::unique_ptr<Stat> modifiedAttack;
   std::unique_ptr<Stat> modifiedDefense;
   std::unique_ptr<Stat> receivedDamageMultiplier;
   void onDeath() override;

protected:
   int gold;
   float scoreModifier;
   float goldModifier;
   Player(int maxHp, int baseAtk, int baseDef, float scoreModifier, float goldModifier, PlayerRace race)
       : Character{maxHp, baseAtk, baseDef},
         gold{0},
         scoreModifier{scoreModifier},
         goldModifier{goldModifier},
         race{race},
         modifiedAttack{std::make_unique<StatViewer>(static_cast<float>(baseAtk))},
         modifiedDefense{std::make_unique<StatViewer>(static_cast<float>(baseDef))},
         receivedDamageMultiplier{std::make_unique<StatViewer>(1.0f)}
   {
   }

   virtual int calculateAttack() const;

public:
   static const char CHAR = '@';
   const PlayerRace race;
   void collectGold(int goldPickedUp);
   char getChar() const override;
   int getScore() const;
   int getGold() const;
   int getAttack() const;
   int getDefense() const;
   int useAttack(Character &c); // Return the damage dealt
   virtual void useStatPotion(StatType type, int amount);
   void modifyStat(StatType type, float amount);
   virtual int calculateDamageTaken(int attackerAtk) override;
};

#endif