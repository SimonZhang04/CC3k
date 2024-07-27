#include "GameView.h"
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
#include <iostream>
#include <string>

char GameView::displayRaces()
{
    std::cout << "Choose a race: h - human, e - elf, d - dwarf, o - orc" << std::endl;
    char c;
    std::cin >> c;

    switch (c)
    {
    case 'h':
    case 'e':
    case 'd':
    case 'o':
        return c;
    default:
        std::cout << "Invalid race, terminating.";
        return INVALID_PLAYER_RACE;
    }
}

void GameView::displayData(const Player &p, const int currentFloor)
{
    std::cout << "Race: " + p.race + " Gold: " + std::to_string(p.getGold()) + "                                                  Floor " + std::to_string(currentFloor) << std::endl;
    std::cout << "HP: " + std::to_string(p.hp) << std::endl;
    std::cout << "Atk: " + std::to_string(p.getAttack()) << std::endl;
    std::cout << "Def: " + std::to_string(p.getDefense()) << std::endl;
};

void GameView::displayAction(std::string playerActions, std::string enemyActions)
{
    std::cout << "Action: " << playerActions << ". ";
    if (enemyActions.length() != 0)
    {
        std::cout << enemyActions;
    }
    std::cout << std::endl;
}

void GameView::displayFloor(Floor &f)
{
    for (int r = 0; r < Floor::FLOOR_ROWS; r++)
    {
        for (int c = 0; c < Floor::FLOOR_COLS; c++)
        {
            bool didPrint = false;
            Tile &t{f.getTile(r, c)};
            for (int i = 0; i < 5; i++)
            {
                // if (f.chambers[i].count(&t))
                // {
                //     std::cout << formatColor(f.getTile(r, c).draw());
                //     didPrint = true;
                //     break;
                // }
            }
            if (!didPrint)
            {
                std::cout << formatColor(f.getTile(r, c).draw());
            }
        }
        std::cout << std::endl;
    }
}

std::string GameView::formatColor(char c)
{
    Color col = charToColor(c);
    std::string colorCode = "";
    switch (col)
    {
    case Color::None:
        return std::string{c};
    case Color::Red:
        colorCode = "31";
        break;
    case Color::Green:
        colorCode = "32";
        break;
    case Color::Yellow:
        colorCode = "33";
        break;
    case Color::Blue:
        colorCode = "34";
        break;
    case Color::Magenta:
        colorCode = "35";
        break;
    case Color::Cyan:
        colorCode = "36";
        break;
    }
    std::string s = "\033[" + colorCode + "m";
    s += c;
    s += "\033[0m";
    return s;
}

Color GameView::charToColor(char c)
{
    switch (c)
    {
    case Player::CHAR:
        return Color::Green;
    case Compass::CHAR:
    case Stairway::CHAR:
        return Color::Cyan;
    case BarrierSuit::CHAR:
        return Color::Blue;
    case Treasure::CHAR:
        return Color::Yellow;
    case Potion::CHAR:
        return Color::Magenta;
    case Vampire::CHAR:
    case Werewolf::CHAR:
    case Goblin::CHAR:
    case Merchant::CHAR:
    case Phoenix::CHAR:
    case Troll::CHAR:
    case Dragon::CHAR:
        return Color::Red;
    }
    return Color::None;
}