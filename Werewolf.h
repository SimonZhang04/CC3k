#include "Enemy.h"

class Werewolf : public Enemy
{
   static const int BASE_HP = 120;
   static const int BASE_ATK = 30;
   static const int BASE_DEF = 5;

public:
   Werewolf(std::unique_ptr<Drawable> loot) : Enemy{BASE_HP, BASE_ATK, BASE_DEF, std::move(loot)} {};
   char getChar() const override { return CHAR; };
   static const char CHAR = 'W';
};