#include "Drawable.h"
class Door : public Drawable
{
public:
    char getChar() const override { return '+'; };
};