#include "Drawable.h"
class FloorTile : public Drawable
{
public:
    char getChar() const override { return '.'; };
};