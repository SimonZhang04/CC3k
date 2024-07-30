#include "GameLogic.h"
#include "Player.h"
#include "Potion.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

const std::vector<std::string> GameLogic::DIRECTIONS = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};
const std::string GameLogic::ATTACK_COMMAND = "a";
const std::string GameLogic::USE_POTION_COMMAND = "u";
const std::string GameLogic::QUIT_COMMAND = "q";
const std::string GameLogic::RESTART_COMMAND = "r";

void GameLogic::notifyDeath(Subject &entity)
{
    Floor &curFloor = gameModel.getCurrentFloor();
    Entity *entityPtr = dynamic_cast<Entity *>(&entity);
    // check if the entity that died is a Player class
    if (&entity == &gameModel.getPlayer())
    {
        gameModel.gameOver = true;
    }
    else
    {
        std::pair<int, int> entityCoords = determineEntityLocation(*entityPtr, curFloor);
        curFloor.replaceEntity(entityCoords.first, entityCoords.second, entityPtr->drawableToReplace());
    }
}

void GameLogic::notifyAction(std::string &action)
{
    gameView.addPlayerAction(action);
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

void GameLogic::playGame(std::string mapFile)
{
    gameModel = GameModel{gameModel.bonusActive};
    char race = gameView.displayRaces();
    std::unique_ptr<Player> player{gameModel.setupPlayer(race)};

    if (!mapFile.empty())
    {
        parseMapFile(mapFile, std::move(player));
    }
    else
    {
        gameModel.generateMap(std::move(player), [this]()
                              { this->onCompassUsed(); }, [this]()
                              { this->onStairsUsed(); }, this);
    }

    mainLoop();
}

void GameLogic::mainLoop()
{
    std::string action;
    gameView.addPlayerAction("has spawned");
    Player &player = gameModel.getPlayer();
    while (true)
    {
        Floor &curFloor = gameModel.getCurrentFloor();
        Tile &curTile = *gameModel.currentTile;

        gameView.displayFloor(gameModel.getCurrentFloor());
        gameView.displayData(player, gameModel.currentFloor);
        gameView.displayActions();
        gameView.resetMessages();

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
                    // If the player reaches the last staircase
                    if (gameModel.gameOver)
                    {
                        break;
                    }
                    // If tile is now valid after effect, move to it
                    if (!t.isValidPlayer())
                    {
                        continue;
                    }
                }
                else
                {
                    gameView.addErrorMessage("Cannot walk to specified tile.");
                    continue;
                }
            }

            // move to the tile (update gameModel and currentTile)
            curTile.moveTo(t);
            gameModel.currentTile = &t;
            gameView.addPlayerAction("moves " + curFloor.stringDirectionMap[action]);
        }
        else if (action == ATTACK_COMMAND)
        {
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

                Enemy *e = curFloor.checkForEnemy(r, c);
                if (e == nullptr)
                {
                    gameView.addErrorMessage("Invalid attack command (attacking non-enemy)");
                    continue;
                }
                char enemyType = e->getChar();
                int enemyHp = e->getHp();
                int damageDealt = player.useAttack(*e);
                enemyHp -= damageDealt;
                // if the enemy is dead, no more access to it
                if (enemyHp > 0)
                {
                    gameView.addPlayerAction("deals " + std::to_string(damageDealt) + " damage to Enemy " + enemyType + " (" + std::to_string(enemyHp) + ")");
                }
            }
            else
            {
                gameView.addErrorMessage("Invalid attack command (invalid direction)"); // Error trying to attack invalid direction
                continue;
            }
        }
        else if (action == USE_POTION_COMMAND)
        {
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

                Potion *p = curFloor.checkForPotion(r, c);
                if (p == nullptr)
                {
                    gameView.addErrorMessage("Invalid use command (not targeting a potion)");
                    continue;
                }
                std::string potionType = p->getPotionType();
                // Check if potion has already been used
                auto it = std::find(gameModel.identifiedItems.begin(), gameModel.identifiedItems.end(), potionType);
                if (it == gameModel.identifiedItems.end())
                {
                    // Potion has not been used, add it to the list
                    gameModel.identifiedItems.push_back(potionType);
                }

                p->consumePotion();
            }
            else
            {
                // Error trying to attack invalid direction
                gameView.addErrorMessage("Invalid attack command");
                continue;
            }
        }
        else if (action == RESTART_COMMAND)
        {
            playGame("");
            return;
        }
        else if (action == QUIT_COMMAND)
        {
            return;
        }
        else
        { // no valid action
            gameView.addErrorMessage("Invalid action.");
            continue;
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
                        std::string enemyAction = enemy->act(player, *gameModel.currentTile);
                        if (enemyAction != "")
                        {
                            gameView.addEnemyAction(std::string(1, enemy->getChar()) + enemyAction);
                        }
                        actedEnemies.insert(enemy);
                    }
                }
            }
        }
        // scan surrounding items
        Tile &movedTile = *gameModel.currentTile;
        std::vector<Tile *> surroundingTiles = gameModel.getCurrentFloor().getSurroundingTiles(movedTile.getRow(), movedTile.getCol());
        gameView.playerScan(surroundingTiles, gameModel.identifiedItems);

        // game over conditions
        if (gameModel.gameOver)
        {
            break;
        }
    }
    bool playAgain = gameView.displayGameOver(player, gameModel.currentFloor, gameModel.LAST_FLOOR);
    if (playAgain)
    {
        playGame("");
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
                                     { this->onCompassUsed(); }, [this]()
                                     { this->onStairsUsed(); }, this);
}

void GameLogic::onCompassUsed()
{
    gameModel.stairs[gameModel.currentFloor]->reveal();
}

void GameLogic::onStairsUsed()
{
    int nextFloor = ++gameModel.currentFloor;
    if (nextFloor == gameModel.LAST_FLOOR)
    {
        gameModel.gameOver = true;
        return;
    }
    gameModel.currentTile->moveTo(*gameModel.startTiles[gameModel.currentFloor]);
    gameModel.currentTile = gameModel.startTiles[gameModel.currentFloor];
    gameModel.getPlayer().onFloorProgressed();
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
