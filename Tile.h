#ifndef TILE
#define TILE

#include "Drawable.h"
#include <memory>
class Tile
{
    std::unique_ptr<Drawable> lower;
    std::unique_ptr<Drawable> upper;

public:
    Tile(std::unique_ptr<Drawable> &&lower, std::unique_ptr<Drawable> &&upper = nullptr) : lower{std::move(lower)}, upper{std::move(upper)} {};
    const char draw() const
    {
        if (upper == nullptr)
        {
            return lower->getChar();
        }
        return upper->getChar();
    }
};

#endif