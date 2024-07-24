#include "GameModel.h"

GameModel::GameModel() : currentFloor{0}, floors{std::vector<Floor>{}}
{
    for (int i = 0; i < 5; i++)
    {
        floors.push_back(Floor{});
    }
};