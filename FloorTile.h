#include "Drawable.h"
class FloorTile : public Drawable
{
public:
    char getChar() override { return '.'; };
};