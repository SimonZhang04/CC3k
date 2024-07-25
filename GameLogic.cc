#include "GameLogic.h"

void GameLogic::playGame()
{
    gameView.displayFloor(gameModel.floors[gameModel.currentFloor]);
}

void GameLogic::generateFloor(Floor &f)
{
    int playerChamber = rand() % 5;
    Tile &t = f.randomTile(playerChamber);
}