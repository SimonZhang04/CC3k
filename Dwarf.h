#include "Player.h"
#include "StatViewer.h"

class Dwarf : public Player
{
public:
   Dwarf::Dwarf() : Player(100, 20, 30, 1, 2) {}
};
