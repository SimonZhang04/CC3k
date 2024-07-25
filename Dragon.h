#include "Enemy.h"

class Dragon : public Enemy
{
   static const int BASE_HP = 150;
   static const int BASE_ATK = 20;
   static const int BASE_DEF = 20;

public:
   Dragon(Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot)} {};
   static const char CHAR = 'D';
   char getChar() const override { return CHAR; };
   virtual bool shouldMove() override;
   virtual void onDeath(Player &p) override;
   virtual bool shouldAttack(Tile &playerTile) override;
};