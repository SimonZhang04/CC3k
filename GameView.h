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

public:
    int displayRaces();
    void displayData(const Player &p, const int &currentFloor);
    void displayAction(std::string playerActions, std::string enemyActions, std::string errorMessage);
    void displayFloor(Floor &f);
    void displayGameOver(const Player &p, const int &currentFloor, const int LAST_FLOOR);
    std::string playerScan(std::vector<Tile *> surroundingTiles, std::vector<std::string> identifiedItems);
    const char INVALID_PLAYER_RACE = ' ';
    std::string playerRaceToString(PlayerRace race);
};
