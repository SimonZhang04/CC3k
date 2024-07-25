#include "Tile.h"
#include "FloorTile.h"
#include <vector>

const int Tile::NUM_NEIGHBORS = 8;

char Tile::draw() const
{
    if (upper == nullptr)
    {
        return lower->getChar();
    }
    return upper->getChar();
}

void Tile::setNeighbors(Tile *n[])
{
    for (int i = 0; i < Tile::NUM_NEIGHBORS; i++)
    {
        neighbors[i] = n[i];
    }
}

std::vector<Tile *> Tile::getValidNeighbors()
{
    std::vector<Tile *> res{};
    for (Tile *t : neighbors)
    {
        if (t != nullptr && t->isValid())
        {
            res.push_back(t);
        }
    }
    return res;
}

bool Tile::isValid() const
{
    return upper == nullptr && typeid(lower) == typeid(FloorTile);
}

void Tile::moveTo(Tile &t)
{
    t.upper = std::move(upper);
};