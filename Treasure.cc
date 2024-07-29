#include "Treasure.h"
#include "StringFormatter.h"

const std::map<TreasureType, int> Treasure::GOLD_MAP = {{TreasureType::NormalTreasure, 1}, {TreasureType::SmallHoard, 2}, {TreasureType::MerchantsHoard, 4}, {TreasureType::DragonHoard, 6}};

void Treasure::useEffect()
{
    float gainedGold = onUse(gold);
    notifyActionObservers("picked up " + StringFormatter::formatFloat(gainedGold) + " gold");
    notifyDeathObservers();
};