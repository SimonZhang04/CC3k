#include "Drawable.h"
class PassageWay : public Drawable
{
public:
    char getChar() const override { return '#'; };
};