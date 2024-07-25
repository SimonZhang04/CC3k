#include "Entity.h"

class EffectObject : public Entity
{
protected:
   virtual void useEffect() = 0;
};