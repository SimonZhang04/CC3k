#include "GameModel.h"
#include "Dragon.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Goblin.h"
#include "Human.h"
#include "Merchant.h"
#include "Orc.h"
#include "Phoenix.h"
#include "Troll.h"
#include "Vampire.h"
#include "Werewolf.h"

GameModel::GameModel() : currentFloor{0}, floors{std::vector<Floor>{}}
{
    for (int i = 0; i < 5; i++)
    {
        floors.push_back(Floor{});
    }
};

const Player &GameModel::setupPlayer(char c)
{
    std::unique_ptr<Player> p;

    switch (c)
    {
    case 'h':
        p = std::make_unique<Human>();
        break;
    case 'e':
        p = std::make_unique<Elf>();
        break;
    case 'd':
        p = std::make_unique<Dwarf>();
        break;
    case 'o':
        p = std::make_unique<Orc>();
        break;
    }

    player = std::move(p);
    return getPlayer();
}

const Player &GameModel::getPlayer()
{
    return *player;
}

void GameModel::createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS])
{
    for (int f = 0; f < 5; f++)
    {
        for (int r = 0; r < Floor::FLOOR_ROWS; r++)
        {
            for (int c = 0; c < Floor::FLOOR_COLS; c++)
            {
                Tile &t = floors[f].getTile(r, c);
                Drawable *d;
                switch (map[f][r][c])
                {
                case Vampire::CHAR:

                    break;
                case Werewolf::CHAR:
                    break;
                case Goblin::CHAR:
                    break;
                case Merchant::CHAR:
                    break;
                case Dragon::CHAR:
                    break;
                case Phoenix::CHAR:
                    break;
                case Troll::CHAR:
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                    // Potions
                    break;
                case '6':
                case '7':
                    // Treasure
                    break;
                case '8':
                case '9':
                    // Protected Treasure
                    break;
                default:
                    break;
                }
            }
        }
    }
}