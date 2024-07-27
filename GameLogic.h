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
    static const bool isDirection(const std::string &direction);
    static const bool isAttackAction(const std::string &action);
    static const bool isUsePotionAction(const std::string &action);
    void getDirectionCoords(int &r, int &c, std::string &dir, Floor &curFloor, Tile &curTile);
    void onCompassUsed();
    void onStairsUsed();
    void notify(Subject &entity) override;
    std::pair<int, int> determineEntityLocation(Entity &entity, Floor &curFloor);

public:
    void playGame(std::string mapFile);
};