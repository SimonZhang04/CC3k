#include "Floor.h"
#include "Compass.h"
#include <map>
#include <functional>
class GameModel
{
    Player *player;

public:
    static const int ENEMIES_PER_FLOOR = 10;
    int currentFloor;
    Tile *currentTile;
    std::vector<Floor> floors;
    GameModel();
    std::unique_ptr<Player> setupPlayer(char c);
    const Player &getPlayer();
    void createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS], std::unique_ptr<Player> player, std::function<void()>);
    std::unique_ptr<Drawable> getEnemyLoot(int compassIdx, int currentCount, std::unique_ptr<Drawable> defaultLoot, std::unique_ptr<Compass> compass)
    {
        if (compassIdx == currentCount)
        {
            return compass;
        }
        else
        {
            return defaultLoot;
        }
    }
};