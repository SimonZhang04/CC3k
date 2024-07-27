#include "Potion.h"
#include "PotionType.h"
#include "Player.h"
#include "StatType.h"
#include <functional>

class StatPotion : public Potion
{
    StatType stat;
    int amount;

public:
    StatPotion(Player &p) : Potion{p} {}

protected:
    void useEffect() override
    {
        player.useStatPotion(stat, amount);
    };
};