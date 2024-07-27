#ifndef ENTITY
#define ENTITY

#include "Drawable.h"
#include <memory>

class Entity : public virtual Drawable
{
public:
   virtual std::unique_ptr<Drawable> drawableToReplace() = 0;
};

#endif