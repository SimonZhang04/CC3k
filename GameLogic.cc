#include "GameLogic.h"
#include "Player.h"
#include <fstream>
#include <functional>

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

    gameView.displayFloor(gameModel.floors[gameModel.currentFloor]);
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
    gameModel.createFloorsFromString(map, [this]()
                                     { this->onCompassUsed(); });
}

void GameLogic::onCompassUsed()
{
}