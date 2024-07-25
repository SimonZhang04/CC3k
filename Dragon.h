#include "Enemy.h"

class Dragon : public Enemy
{
   const int BASE_HP = 150;
   const int BASE_ATK = 20;
   const int BASE_DEF = 20;

public:
   Dragon::Dragon() : Enemy(BASE_HP, BASE_ATK, BASE_DEF) {};
   char getChar() const override { return 'D'; };
   virtual bool shouldMove() override;
   virtual void onDeath(Player &p) override;
   virtual bool shouldAttack(Tile &playerTile) override;
};