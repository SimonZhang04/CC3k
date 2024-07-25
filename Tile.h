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
    bool isValidEnemy() const;
    bool isValidPlayer() const;
    void moveTo(Tile &t);
    int getRow() const { return r; };
    int getCol() const { return c; };
    Drawable *getUpper() { return upper.get(); };
    void setUpperDrawable(std::unique_ptr<Drawable> newUpper);
};

#endif