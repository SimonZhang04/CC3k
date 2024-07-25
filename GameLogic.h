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
    void parseMapFile(std::string mapFile, std::unique_ptr<Player> player);
    static const std::vector<std::string> DIRECTIONS;
    static const bool isDirection(const std::string &direction);
    static const bool isAttack(const std::string &action);
    void getDirectionCoords(int &r, int &c, std::string &dir, Floor &curFloor, Tile &curTile);
    void onCompassUsed();

public:
    void playGame(std::string mapFile);
};