#ifndef FLOOR
#define FLOOR

#include "Tile.h"
#include <vector>
#include <string>
class Floor
{

    std::vector<std::vector<Tile>> chambers;

    std::vector<std::vector<Tile>> tiles;

public:
    Floor();
    const Tile &getTile(int r, int c) const;
};

#endif
