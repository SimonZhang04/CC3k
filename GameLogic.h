#include "GameView.h"
#include "GameModel.h"

class GameLogic
{
    GameView gameView;
    GameModel gameModel;
    void generateFloor(Floor &f);

public:
    void playGame();
};