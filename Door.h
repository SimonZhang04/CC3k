#include "Drawable.h"
class Door : public Drawable
{
public:
    char getChar() override { return '+'; };
};