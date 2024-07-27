#include "Floor.h"
#include "Compass.h"
#include <map>
#include <functional>
class GameModel
{
    Player *player;

public:
    static const int ENEMIES_PER_FLOOR = 10;
    static const std::map<char, int> ENEMY_SPAWN_WEIGHTS;
    int currentFloor;
    Tile *currentTile;
    std::vector<Floor> floors;
    GameModel();
    std::unique_ptr<Player> setupPlayer(char c);
    Floor &getCurrentFloor();
    Player &getPlayer();
    std::unique_ptr<Enemy> instantiateEnemy(char enemy, Tile *t, std::unique_ptr<Compass> &compass);
    void createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS], std::unique_ptr<Player> player, std::function<void()>);
    void generateFloor(Floor &f, std::function<void()> onCompassPickup);
    int randomStairChamber(int playerChamber);
};