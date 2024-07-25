#include "Drawable.h"
class VertWall : public Drawable
{
public:
    char getChar() const override { return '|'; };
};