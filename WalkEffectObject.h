#include "EffectObject.h"

class WalkEffectObject : public EffectObject
{
public:
   virtual void onWalkedOn() = 0;
   virtual Drawable *drawableToReplace() override { return nullptr; };
};