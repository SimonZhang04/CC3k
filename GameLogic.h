#include "Enemy.h"
#include "GameModel.h"
#include "GameView.h"

class GameLogic
{
    GameView gameView;
    GameModel gameModel;
    int randomStairChamber(int playerChamber);
    void generateFloor(Floor &f);
    Enemy *randomEnemy();
    void parseMapFile(std::string mapFile);
    static const std::vector<std::string> DIRECTIONS;
    static const bool isDirection(const std::string &direction);
    void onCompassUsed();

public:
    void playGame(std::string mapFile);
};