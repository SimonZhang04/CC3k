#include "GameView.h"
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

void GameView::displayFloor()
{
}
