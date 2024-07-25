#include "Tile.h"
#include "FloorTile.h"
#include <vector>
#include <iostream>

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
        if (t != nullptr && t->isValidEnemy())
        {
            res.push_back(t);
        }
    }
    return res;
}

bool Tile::isValidEnemy() const
{
    return upper == nullptr && typeid(*lower) == typeid(FloorTile);
}

bool Tile::isValidPlayer() const
{
    return upper == nullptr;
}

void Tile::moveTo(Tile &t)
{
    std::cout << draw() << std::endl;
    t.upper = std::move(upper);
    // std::cout << t.upper->getChar() << std::endl;
    upper = nullptr;
};

void Tile::setUpperDrawable(std::unique_ptr<Drawable> newUpper)
{
    upper = std::move(newUpper);
}
