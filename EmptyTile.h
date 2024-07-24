#include "Drawable.h"
class EmptyTile : public Drawable
{
public:
    char getChar() override { return ' '; };
};