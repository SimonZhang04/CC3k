#include "Drawable.h"
class HorizWall : public Drawable
{
public:
    char getChar() const override { return '-'; };
};