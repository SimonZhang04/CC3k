#include "Elf.h"

// implement later

void Elf::useStatPotion(StatType type, int amount)
{
    Player::useStatPotion(type, abs(amount));
};
