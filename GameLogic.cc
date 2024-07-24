#include "GameLogic.h"

void GameLogic::playGame()
{
    gameView.displayFloor(gameModel.floors[gameModel.currentFloor]);
}