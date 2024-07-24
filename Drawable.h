#ifndef DRAWABLE
#define DRAWABLE

class Drawable
{
public:
    virtual char getChar() const = 0;
    virtual ~Drawable() {};
};

#endif