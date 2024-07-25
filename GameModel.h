#include "Floor.h"
#include <map>
class GameModel
{
    std::unique_ptr<Player> player;

public:
    static const int ENEMIES_PER_FLOOR = 10;
    int currentFloor;
    Tile *currentTile;
    std::vector<Floor> floors;
    GameModel();
    const Player &setupPlayer(char c);
    const Player &getPlayer();
    void createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS]);
};