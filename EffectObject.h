#ifndef EFFECTOBJECT
#define EFFECTOBJECT

#include "Entity.h"

class EffectObject : public virtual Entity
{
protected:
   virtual void useEffect() = 0;
   std::unique_ptr<Drawable> drawableToReplace() override { return nullptr; };
};

#endif
