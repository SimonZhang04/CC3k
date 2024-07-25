#include "Drawable.h"

class Entity : public Drawable
{
public:
   virtual Drawable *drawableToReplace() = 0;
};