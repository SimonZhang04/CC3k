#include "GameLogic.h"
#include "Player.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>

const std::vector<std::string> GameLogic::DIRECTIONS = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};

const bool GameLogic::isDirection(const std::string &direction)
{
    return std::find(GameLogic::DIRECTIONS.begin(), GameLogic::DIRECTIONS.end(), direction) != GameLogic::DIRECTIONS.end();
}

const bool GameLogic::isAttack(const std::string &action)
{
    return action == "a";
}

void GameLogic::playGame(std::string mapFile)
{
    char race = gameView.displayRaces();
    if (race == gameView.INVALID_PLAYER_RACE)
    {
        return;
    }

    std::unique_ptr<Player> player{gameModel.setupPlayer(race)};

    if (!mapFile.empty())
    {
        parseMapFile(mapFile, std::move(player));
    }
    else
    {
        // Do map generation
    }

    // Game loop
    std::string action;
    std::string playerActions = "Player character has spawned";
    std::string enemyActions = "";
    while (true)
    {
        Floor &curFloor = gameModel.getCurrentFloor();
        Tile &curTile = *gameModel.currentTile;

        gameView.displayFloor(curFloor);
        gameView.displayData(gameModel.getPlayer(), gameModel.currentFloor);
        gameView.displayAction(playerActions, enemyActions);
        playerActions = "PC ";
        enemyActions = "";
        // Accept an action
        std::cin >> action;
        if (isDirection(action))
        {

            int r, c;
            try
            {
                getDirectionCoords(r, c, action, curFloor, curTile);
            }
            catch (const std::exception &e)
            {
                continue;
            }
            // check if tile is valid
            if (!curFloor.getTile(r, c).isValidPlayer())
            {
                continue;
            }

            // move to the tile (update gameModel and currentTile)
            curTile.moveTo(curFloor.getTile(r, c));
            gameModel.currentTile = &curFloor.getTile(r, c);

            // add action to playerActions
            playerActions += "moves " + gameModel.floors[gameModel.currentFloor].stringDirectionMap[action];
        }
        else if (isAttack(action))
        {
            std::cin >> action;
            if (isDirection(action))
            {
                int r, c;
                try
                {
                    getDirectionCoords(r, c, action, curFloor, curTile);
                }
                catch (std::exception e)
                {
                    continue;
                }

                Enemy *e = curFloor.checkForEnemy(r, c);
                if (e == nullptr)
                {
                    continue;
                    // Error: trying to attack something that isn't an enemy
                }
                gameModel.getPlayer().useAttack(*e);
            }
            else
            {
                // Error trying to attack invalid direction
            }
        }
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

void GameLogic::parseMapFile(std::string mapFile, std::unique_ptr<Player> player)
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
    gameModel.createFloorsFromString(map, std::move(player), [this]()
                                     { this->onCompassUsed(); });
}

void GameLogic::onCompassUsed()
{
}

void GameLogic::getDirectionCoords(int &r, int &c, std::string &dirstr, Floor &curFloor, Tile &curTile)
{
    r = curTile.getRow();
    c = curTile.getCol();

    int dir = curFloor.directionMap[dirstr];
    curFloor.directionToCoordinate(r, c, dir);
    // check if coord is in floor bounds
    if (!curFloor.inBounds(r, c))
    {
        throw std::exception();
    }
}