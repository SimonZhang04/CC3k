#ifndef TILE
#define TILE

#include "Drawable.h"
#include <memory>
#include <vector>
class Tile
{
    int r, c;
    std::unique_ptr<Drawable> lower;
    std::unique_ptr<Drawable> upper;
    Tile *neighbors[8];

public:
    static const int NUM_NEIGHBORS;
    Tile(int r, int c, std::unique_ptr<Drawable> &&lower, std::unique_ptr<Drawable> &&upper = nullptr) : r{r}, c{c}, lower{std::move(lower)}, upper{std::move(upper)} {};
    std::vector<Tile *> getValidNeighbors();
    void setNeighbors(Tile *n[]);
    char draw() const;
    bool isValid() const;
};

#endif