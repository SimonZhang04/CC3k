#include "Color.h"
#include "BarrierSuit.h"
#include "Compass.h"
#include "Dragon.h"
#include "Goblin.h"
#include "Merchant.h"
#include "Phoenix.h"
#include "Potion.h"
#include "Stairway.h"
#include "Tile.h"
#include "Treasure.h"
#include "Troll.h"
#include "Vampire.h"
#include "Werewolf.h"
#include <sstream>
#include <string>
#include <iomanip>

class StringFormatter
{
public:
    static std::string formatFloat(float f);
    static std::string formatColor(char c);
    static Color charToColor(char c);
};
