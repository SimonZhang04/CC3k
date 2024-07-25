#include "Enemy.h"

class Merchant : public Enemy
{
   const int BASE_HP = 30;
   const int BASE_ATK = 70;
   const int BASE_DEF = 5;
   static bool isAggro;

public:
   Merchant(std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'M';
   virtual bool shouldAttack(Tile &playerTile) override;
   virtual void onDeath(Player &p) override;
};