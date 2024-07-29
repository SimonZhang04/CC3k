#include "Enemy.h"

class Merchant : public Enemy
{
   static const int BASE_HP = 30;
   static const int BASE_ATK = 70;
   static const int BASE_DEF = 5;
   static bool isAggro;

public:
   Merchant(Tile *occupyingTile, std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, occupyingTile, std::move(loot), 0} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'M';
   virtual void onReceiveAttack() override;
   virtual bool shouldAttack(Tile &playerTile) override;
};
