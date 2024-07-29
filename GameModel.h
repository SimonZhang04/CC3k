#include "Compass.h"
#include "Floor.h"
#include "Observer.h"
#include "Stairway.h"
#include <functional>
#include <map>
class GameModel
{
    Player *player;
    static const std::map<char, int> ENEMY_SPAWN_WEIGHTS;
    static const std::map<char, int> TREASURE_SPAWN_WEIGHTS;
    static const std::map<char, int> POTION_SPAWN_WEIGHTS;
    static const int ENEMIES_PER_FLOOR = 10;
    static const int POTIONS_PER_FLOOR = 10;
    static const int TREASURE_PER_FLOOR = 10;
    static const std::unordered_set<char> PROTECTED_TREASURE_CHARS;

public:
    static const int LAST_FLOOR = 5;
    bool gameOver = false;

    int currentFloor;
    Tile *currentTile;
    std::vector<Floor> floors;
    std::vector<std::string> identifiedItems;
    Stairway *stairs[5];
    Tile *startTiles[5];
    GameModel();
    std::unique_ptr<Player> setupPlayer(char c);
    Floor &getCurrentFloor();
    Player &getPlayer();
    std::unique_ptr<Enemy> instantiateEnemy(char enemy, Tile *t, std::unique_ptr<Compass> &compass, Observer *gameLogic);
    void createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS], std::unique_ptr<Player> player, std::function<void()> onCompassUsed, std::function<void()> onStairsUsed, Observer *gameLogic);
    void generateMap(std::unique_ptr<Player> player, std::function<void()> onCompassUsed, std::function<void()> onStairsUsed, Observer *gameLogic);
    void genProtectedTreasure(char protectedTreasure, Floor &floor, std::string (&map)[Floor::FLOOR_ROWS], int &dragonCount);
    void placeInChamber(char c, int chamber, Floor &floor, std::string (&map)[Floor::FLOOR_ROWS]);
    int randomStairChamber(int playerChamber);
};
