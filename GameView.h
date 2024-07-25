#include "Floor.h"

class GameView
{
    std::string formatColor(char c);

public:
    char displayRaces();
    void displayData(const Player &p, const int currentFloor);
    void displayAction();
    void displayFloor(Floor &f);
    const char INVALID_PLAYER_RACE = ' ';
};