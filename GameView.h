#include "Floor.h"

class GameView
{
    std::string formatColor(char c);

public:
    void displayRaces();
    void displayData();
    void displayAction();
    void displayFloor(Floor &f);
};