#include "GameView.h"
#include "GameModel.h"
#include "Enemy.h"

class GameLogic
{
    GameView gameView;
    GameModel gameModel;
    int randomStairChamber(int playerChamber);
    void generateFloor(Floor &f);
    Enemy *randomEnemy();
    void parseMapFile(std::string mapFile);

public:
    void playGame(std::string mapFile);
};