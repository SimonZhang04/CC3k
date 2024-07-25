#include "GameLogic.h"
#include "Player.h"
#include <algorithm>
#include <fstream>
#include <iostream>

const std::vector<std::string> GameLogic::DIRECTIONS = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};

const bool GameLogic::isDirection(const std::string &direction)
{
    return std::find(GameLogic::DIRECTIONS.begin(), GameLogic::DIRECTIONS.end(), direction) != GameLogic::DIRECTIONS.end();
}

void GameLogic::playGame(std::string mapFile)
{

    char race = gameView.displayRaces();
    if (race == gameView.INVALID_PLAYER_RACE)
    {
        return;
    }

    const Player &player = gameModel.getPlayer();

    if (!mapFile.empty())
    {
        parseMapFile(mapFile);
    }
    else
    {
        // Do map generation
    }

    // Game loop
    std::string action;
    while (true)
    {
        gameView.displayFloor(gameModel.floors[gameModel.currentFloor]);
        gameView.displayData(gameModel.getPlayer(), gameModel.currentFloor);
        gameView.displayAction();
        // Accept an action
        std::cin >> action;
        if (isDirection(action))
        {
            int row = gameModel.currentTile->getRow();
            int col = gameModel.currentTile->getCol();
            int dir = gameModel.floors[gameModel.currentFloor].directionMap[action];
            gameModel.floors[gameModel.currentFloor].directionToCoordinate(row, col, dir);
            // check if coord is in floor bounds
            if (!gameModel.floors[gameModel.currentFloor].inBounds(row, col))
            {
                continue;
            }

            // check if tile is valid
            if (!gameModel.floors[gameModel.currentFloor].getTile(row, col).isValid())
            {
                continue;
            }

            // move to the tile (update gameModel and currentTile)
            gameModel.currentTile->moveTo(gameModel.floors[gameModel.currentFloor].getTile(row, col));
            gameModel.currentTile = &gameModel.floors[gameModel.currentFloor].getTile(row, col);
        };
    }
}

void GameLogic::generateFloor(Floor &f)
{
    int playerChamber = rand() % 5;
    Tile &t = f.randomTile(playerChamber);
    f.RemoveTileFromChamber(&t, playerChamber);

    int stairChamber = randomStairChamber(playerChamber);
    // deal with this

    // gameModel.floors[gameModel.currentFloor]

    for (int i = 0; i < GameModel::ENEMIES_PER_FLOOR; i++)
    {
        Enemy *e = randomEnemy();
    }
}

int GameLogic::randomStairChamber(int playerChamber)
{
    int stairchambers[4];
    int cur = 0;
    for (int i = 0; i < 5; i++)
    {
        if (i != playerChamber)
        {
            stairchambers[cur] = i;
            cur++;
        }
    }
    return stairchambers[rand() % 4];
}

Enemy *GameLogic::randomEnemy() {
};

void GameLogic::parseMapFile(std::string mapFile)
{
    std::fstream filestream{mapFile};
    std::string rowstr;
    std::string map[5][Floor::FLOOR_ROWS];
    for (int f = 0; f < 5; f++)
    {
        for (int r = 0; r < Floor::FLOOR_ROWS; r++)
        {
            std::getline(filestream, rowstr);
            map[f][r] = rowstr;
        }
    }
    gameModel.createFloorsFromString(map);
}