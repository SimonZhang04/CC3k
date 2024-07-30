#include "Floor.h"
#include "Treasure.h"
#include "Color.h"

class GameView
{
    std::vector<std::string> playerActions;
    std::vector<std::string> enemyActions;
    std::string errorMessage;

public:
    static std::string formatFloat(float f);
    int displayRaces();
    void displayData(const Player &p, const int &currentFloor);
    void displayActions();
    void displayFloor(Floor &f);
    bool displayGameOver(const Player &p, const int &currentFloor, const int LAST_FLOOR);
    void addPlayerAction(std::string action);
    void addEnemyAction(std::string action);
    void addErrorMessage(std::string action);
    void resetMessages();
    void playerScan(std::vector<Tile *> surroundingTiles, std::vector<std::string> identifiedItems);
    const char INVALID_PLAYER_RACE = ' ';
    std::string playerRaceToString(PlayerRace race);
};
