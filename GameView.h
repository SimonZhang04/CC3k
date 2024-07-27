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
    char displayRaces();
    void displayData(const Player &p, const int currentFloor);
    void displayAction(std::string playerActions, std::string enemyActions);
    void displayFloor(Floor &f);
    const char INVALID_PLAYER_RACE = ' ';
};
