#include "Enemy.h"

class Dragon : public Enemy
{
   const int BASE_HP = 150;
   const int BASE_ATK = 20;
   const int BASE_DEF = 20;

public:
   Dragon(std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, std::move(loot)} {};
   static const char CHAR = 'D';
   char getChar() const override { return CHAR; };
   virtual bool shouldMove() override;
   virtual void onDeath(Player &p) override;
   virtual bool shouldAttack(Tile &playerTile) override;
};