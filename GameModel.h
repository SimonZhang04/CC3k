#include "Compass.h"
#include "Floor.h"
#include "Observer.h"
#include "Stairway.h"
#include <map>
#include <functional>
#include <map>
class GameModel
{
    Player *player;

public:
    static const int ENEMIES_PER_FLOOR = 10;
    static const std::map<char, int> ENEMY_SPAWN_WEIGHTS;
    int currentFloor;
    Tile *currentTile;
    std::vector<Floor> floors;
    Stairway *stairs[5];
    Tile *startTiles[5];
    GameModel();
    std::unique_ptr<Player> setupPlayer(char c);
    Floor &getCurrentFloor();
    Player &getPlayer();
    std::unique_ptr<Enemy> instantiateEnemy(char enemy, Tile *t, std::unique_ptr<Compass> &compass, Observer *gameLogic);
    void createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS], std::unique_ptr<Player> player, std::function<void()> onCompassUsed, std::function<void()> onStairsUsed, Observer *gameLogic);
    void generateFloor(Floor &f, std::function<void()> onCompassPickup);
    int randomStairChamber(int playerChamber);
};