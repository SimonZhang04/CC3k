#include "Drawable.h"

class Tile
{
    std::unique_ptr<Drawable> lower;
    std::unique_ptr<Drawable> upper;

public:
    Tile(std::unique_ptr<Drawable> &&lower, std::unique_ptr<Drawable> &&upper = nullptr) : lower{std::move(lower)}, upper{std::move(upper)} {};
};