#ifndef WALKEFFECTOBJECT
#define WALKEFFECTOBJECT

#include "EffectObject.h"

class WalkEffectObject : public EffectObject
{
public:
   void onWalkedOn() { useEffect(); };
   virtual std::unique_ptr<Drawable> drawableToReplace() override { return nullptr; };
};

#endif