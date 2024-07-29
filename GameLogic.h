#include "Enemy.h"
#include "Entity.h"
#include "GameModel.h"
#include "GameView.h"
#include "Observer.h"
#include <utility>
#include <vector>

class GameLogic : public Observer
{
    GameView gameView;
    GameModel gameModel;
    void generateFloor(Floor &f);
    void parseMapFile(std::string mapFile, std::unique_ptr<Player> player);
    static const std::vector<std::string> DIRECTIONS;
    static const std::string ATTACK_COMMAND;
    static const std::string USE_POTION_COMMAND;
    static const std::string QUIT_COMMAND;
    static const std::string RESTART_COMMAND;
    static const bool isDirection(const std::string &direction);
    void getDirectionCoords(int &r, int &c, std::string &dir, Floor &curFloor, Tile &curTile);
    void onCompassUsed();
    void onStairsUsed();
    void notifyDeath(Subject &entity) override;
    void notifyAction(std::string &action) override;
    std::pair<int, int> determineEntityLocation(Entity &entity, Floor &curFloor);
    void mainLoop();

public:
    void playGame(std::string mapFile);
};