#include "GameLogic.h"
#include "Player.h"
#include "Potion.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <utility>
#include <vector>

const std::vector<std::string> GameLogic::DIRECTIONS = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};

void GameLogic::notify(Subject &entity)
{
    std::cout << "Game Logic notified about death entity" << std::endl;
    Floor &curFloor = gameModel.getCurrentFloor();
    // type cast entity
    Entity *entityPtr = dynamic_cast<Entity *>(&entity);

    std::pair<int, int> entityCoords = determineEntityLocation(*entityPtr, curFloor);
    curFloor.replaceEntity(entityCoords.first, entityCoords.second, entityPtr->drawableToReplace());
}

std::pair<int, int> GameLogic::determineEntityLocation(Entity &entity, Floor &curFloor)
{
    for (int row = 0; row < curFloor.FLOOR_ROWS; ++row)
    {
        for (int col = 0; col < curFloor.FLOOR_COLS; ++col)
        {
            if (curFloor.getTile(row, col).getUpper() == &entity)
            {
                return std::make_pair(row, col);
            }
        }
    }
    return std::make_pair(-1, -1); // entity not found
}

const bool GameLogic::isDirection(const std::string &direction)
{
    return std::find(GameLogic::DIRECTIONS.begin(), GameLogic::DIRECTIONS.end(), direction) != GameLogic::DIRECTIONS.end();
}

const bool GameLogic::isAttackAction(const std::string &action)
{
    return action == "a";
}

const bool GameLogic::isUsePotionAction(const std::string &action)
{
    return action == "u";
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
            Tile &t = curFloor.getTile(r, c);
            if (!t.isValidPlayer())
            {
                // check if occupied by walkEffectObject
                WalkEffectObject *wo = dynamic_cast<WalkEffectObject *>(t.getUpper());
                if (wo != nullptr)
                {
                    wo->onWalkedOn();
                }
                continue;
            }

            // move to the tile (update gameModel and currentTile)
            curTile.moveTo(t);
            gameModel.currentTile = &t;

            // add action to playerActions
            playerActions += "moves " + curFloor.stringDirectionMap[action];
        }
        else if (isAttackAction(action))
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
        else if (isUsePotionAction(action))
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

                Potion *p = curFloor.checkForPotion(r, c);
                if (p == nullptr)
                {
                    continue;
                    // Error: trying to attack something that isn't an enemy
                }
                p->consumePotion();
            }
            else
            {
                // Error trying to attack invalid direction
            }
        }

        // Enemies act
        // Hash set to keep track of enemies that have acted
        std::unordered_set<Enemy *> actedEnemies;

        // iterate through all tiles on the floor
        for (int row = 0; row < Floor::FLOOR_ROWS; row++)
        {
            for (int col = 0; col < Floor::FLOOR_COLS; col++)
            {
                // check if tile upper is an enemy
                Enemy *enemy = curFloor.checkForEnemy(row, col);
                if (enemy != nullptr)
                {
                    // check if the Enemy is in Hashset
                    if (actedEnemies.find(enemy) == actedEnemies.end())
                    {
                        enemy->act(gameModel.getPlayer(), *gameModel.currentTile);
                        actedEnemies.insert(enemy);
                    }
                }
            }
        }
    }
}

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
                                     { this->onCompassUsed(); }, this);
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