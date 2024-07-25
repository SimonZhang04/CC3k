#include "Player.h"
#include "StatViewer.h"

class Orc : public Player
{
public:
   Orc::Orc() : Player(180, 30, 25, 1, 0.5) {}
};
