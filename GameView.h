#include "Floor.h"
#include "Treasure.h"

enum class Color
{
    Red,
    Yellow,
    Blue,
    Green,
    Cyan,
    Magenta,
    None
};

class GameView
{
    std::string formatColor(char c);
    Color charToColor(char c);
    std::vector<std::string> playerActions;
    std::vector<std::string> enemyActions;
    std::string errorMessage;

public:
    int displayRaces();
    void displayData(const Player &p, const int &currentFloor);
    void displayActions();
    void displayFloor(Floor &f);
    void displayGameOver(const Player &p, const int &currentFloor, const int LAST_FLOOR);
    void addPlayerAction(std::string action);
    void addEnemyAction(std::string action);
    void addErrorMessage(std::string action);
    void resetMessages();
    void playerScan(std::vector<Tile *> surroundingTiles, std::vector<std::string> identifiedItems);
    const char INVALID_PLAYER_RACE = ' ';
    std::string playerRaceToString(PlayerRace race);
};
