#include "GameView.h"
#include "Tile.h"
#include <iostream>

void GameView::displayRaces()
{
    std::cout << "Choose a race: h - human, e - elf, d - dwarf, o - orc";
    char c;
    std::cin >> c;

    switch (c)
    {
    case 'h':
        break;
    case 'e':
        break;
    case 'd':
        break;
    case 'o':
        break;
    default:
        std::cout << "Invalid race, terminating.";
        break;
    }
}

void GameView::displayData()
{
}

void GameView::displayAction()
{
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