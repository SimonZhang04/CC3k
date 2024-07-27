#include "GameView.h"
#include "Tile.h"
#include <iostream>
#include <string>

char GameView::displayRaces()
{
    std::cout << "Choose a race: h - human, e - elf, d - dwarf, o - orc";
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
    std::cout << "Damage Taken Modifier: " + std::to_string(p.receivedDamageMultiplier->getStat()) << std::endl;
};

void GameView::displayAction(std::string playerActions, std::string enemyActions)
{
    std::cout << "Action: " << playerActions << ".";
    if (enemyActions.length() != 0)
    {
        std::cout << enemyActions << ".";
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
                std::cout << f.getTile(r, c).draw();
            }
        }
        std::cout << std::endl;
    }
}

std::string GameView::formatColor(char c)
{
    std::string s = "\033[31mbold" + c;
    s += "\033[0m\n";
    return s;
}