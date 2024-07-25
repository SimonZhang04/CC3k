#ifndef FLOOR
#define FLOOR

#include "Enemy.h"
#include "Tile.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class Floor
{
    std::vector<std::vector<Tile>> tiles;
    std::vector<std::set<Tile *>> chambers;
    void setupChambers();

public:
    static const int FLOOR_ROWS = 25;
    static const int FLOOR_COLS = 79;
    static void directionToCoordinate(int &r, int &c, int dir);
    static bool inBounds(int r, int c);

    Enemy *compassHolder;

    Floor();

    Tile &randomTile(int chamber);
    Tile &getTile(int r, int c);
    void RemoveTileFromChamber(Tile *t, int chamber);
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
};

#endif
