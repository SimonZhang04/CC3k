#include "Player.h"
#include "Potion.h"
#include "PotionType.h"
#include "StatType.h"
#include <functional>
class StatPotion : public Potion
{
    StatType stat;
    int amount;

public:
    StatPotion(Player &p, PotionType type, StatType stat, int amount) : Potion{p, type}, stat{stat}, amount{amount} {}

protected:
    void useEffect() override
    {
        player.useStatPotion(stat, amount);
    };
};
