#include "Enemy.h"
#include "ProtectedTreasure.h"

class Dragon : public Enemy
{
   static const int BASE_HP = 150;
   static const int BASE_ATK = 20;
   static const int BASE_DEF = 20;
   ProtectedTreasure *protectedTreasure;
   virtual void onDeath(Character &attacker) override;
   int protectedTreasureRow;
   int protectedTreasureCol;

public:
   Dragon(Tile *occupyingTile, std::unique_ptr<Drawable> loot, ProtectedTreasure *protectedTreasure, int ptrow, int ptcol)
       : Enemy{BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot), 0},
         protectedTreasure{protectedTreasure},
         protectedTreasureRow{ptrow},
         protectedTreasureCol{ptcol} {};
   static const char CHAR = 'D';
   char getChar() const override { return CHAR; };
   virtual bool shouldMove() override;
   virtual bool shouldAttack(Tile &playerTile) override;
};
