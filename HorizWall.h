#include "Drawable.h"
class HorizWall : public Drawable
{
public:
    char getChar() override { return '-'; };
};