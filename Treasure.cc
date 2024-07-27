#include "Treasure.h"

const std::map<TreasureType, int> Treasure::GOLD_MAP = {{TreasureType::NormalTreasure, 1}, {TreasureType::SmallHoard, 2}, {TreasureType::MerchantsHoard, 4}, {TreasureType::DragonHoard, 6}};
