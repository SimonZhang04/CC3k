#ifndef FLOOR
#define FLOOR

#include "Drawable.h"
#include "Enemy.h"
#include "Tile.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class Potion;

class Floor
{
    std::vector<std::vector<Tile>> tiles;
    std::vector<std::set<Tile *>> chambers;
    void setupChambers();

public:
    static const int FLOOR_ROWS = 25;
    static const int FLOOR_COLS = 79;
    static const std::string DEFAULT_LAYOUT[FLOOR_ROWS];
    static void directionToCoordinate(int &r, int &c, int dir);
    static bool inBounds(int r, int c);

    Floor();

    Tile &popRandomTile(int chamber);
    Tile &getTile(int r, int c);
    void RemoveTileFromChamber(Tile *t, int chamber);
    void replaceEntity(int r, int c, std::unique_ptr<Drawable> newUpper);
    Enemy *checkForEnemy(int r, int c);
    Potion *checkForPotion(int r, int c);
    std::map<std::string, int> directionMap = {
        {"no", 0}, // north
        {"ne", 1}, // northeast
        {"ea", 2}, // east
        {"se", 3}, // southeast
        {"so", 4}, // south
        {"sw", 5}, // southwest
        {"we", 6}, // west
        {"nw", 7}  // northwest
    };
    std::map<std::string, std::string> stringDirectionMap = {
        {"no", "North"},     // north
        {"ne", "Northeast"}, // northeast
        {"ea", "East"},      // east
        {"se", "Southeast"}, // southeast
        {"so", "South"},     // south
        {"sw", "Southwest"}, // southwest
        {"we", "West"},      // west
        {"nw", "Northwest"}  // northwest
    };
};

#endif
