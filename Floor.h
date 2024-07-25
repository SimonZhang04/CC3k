#ifndef FLOOR
#define FLOOR

#include "Tile.h"
#include <vector>
#include <string>
#include <set>
class Floor
{
    std::vector<std::vector<Tile>> tiles;
    std::vector<std::set<Tile *>> chambers;
    void setupChambers();
    bool inBounds(int r, int c);
    void directionToCoordinate(int &r, int &c, int dir);

public:
    static const int FLOOR_ROWS = 25;
    static const int FLOOR_COLS = 79;
    Tile &randomTile(int chamber);
    Floor();
    Tile &getTile(int r, int c);
};

#endif
