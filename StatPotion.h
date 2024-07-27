#include "Potion.h"
#include "PotionType.h"
#include "Player.h"
#include "StatType.h"
#include <functional>
#include <iostream>
class StatPotion : public Potion
{
    StatType stat;
    int amount;

public:
    StatPotion(Player &p, StatType stat, int amount) : Potion{p}, stat{stat}, amount{amount} {}

protected:
    void useEffect() override
    {
        std::cout << &player << std::endl;
        player.useStatPotion(stat, amount);
    };
};