#include "Drawable.h"
class EmptyTile : public Drawable
{
public:
    char getChar() const override { return CHAR; };
    static const char CHAR = ' ';
};