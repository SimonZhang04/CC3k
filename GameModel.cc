#include "GameModel.h"
#include "BarrierSuit.h"
#include "Dragon.h"
#include "DragonHoard.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Goblin.h"
#include "Human.h"
#include "Merchant.h"
#include "Observer.h"
#include "Orc.h"
#include "Phoenix.h"
#include "Randomizer.h"
#include "StatPotion.h"
#include "Treasure.h"
#include "Troll.h"
#include "Vampire.h"
#include "Werewolf.h"
#include <exception>
#include <iostream>

const std::map<char, int> GameModel::ENEMY_SPAWN_WEIGHTS = {{Werewolf::CHAR, 4}, {Vampire::CHAR, 3}, {Goblin::CHAR, 5}, {Troll::CHAR, 2}, {Phoenix::CHAR, 2}, {Merchant::CHAR, 2}};
const std::map<char, int> GameModel::TREASURE_SPAWN_WEIGHTS = {{'6', 5}, {'7', 2}, {'8', 0}, {'9', 1}};
const std::map<char, int> GameModel::POTION_SPAWN_WEIGHTS = {{'0', 1}, {'1', 1}, {'2', 1}, {'3', 1}, {'4', 1}, {'5', 1}};

GameModel::GameModel() : currentFloor{0},
                         floors{std::vector<Floor>{}}
{
    for (int i = 0; i < 5; i++)
    {
        floors.push_back(Floor{});
    }
};

std::unique_ptr<Player> GameModel::setupPlayer(char c)
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

    player = p.get();

    return p;
}

Player &GameModel::getPlayer()
{
    return *player;
}

void GameModel::generateMap(std::unique_ptr<Player> player, std::function<void()> onCompassUsed, std::function<void()> onStairsUsed, Observer *gameLogic)
{
    std::string map[5][Floor::FLOOR_ROWS];
    int barrierFloor = rand() % 5;
    for (int f = 0; f < 5; f++)
    {
        for (int r = 0; r < Floor::FLOOR_ROWS; r++)
        {
            map[f][r] = Floor::DEFAULT_LAYOUT[r];
        }

        Floor &floor = floors[f];
        int dragonCount = 0;

        int playerChamber = rand() % 5;
        placeInChamber(Player::CHAR, playerChamber, floor, map[f]);
        // Tile &playerTile = floor.popRandomTile(playerChamber);
        // map[f][playerTile.getRow()][playerTile.getCol()] = Player::CHAR;

        // int stairChamber = randomStairChamber(playerChamber);
        // Tile &stairTile = floor.popRandomTile(stairChamber);
        // map[f][stairTile.getRow()][stairTile.getCol()] = Stairway::CHAR;
        placeInChamber(Stairway::CHAR, randomStairChamber(playerChamber), floor, map[f]);

        for (int i = 0; i < GameModel::POTIONS_PER_FLOOR; i++)
        {
            char potion = Randomizer<char>::determineRandom(POTION_SPAWN_WEIGHTS);
            // Tile &t = floor.popRandomTile(rand() % 5);
            // map[f][t.getRow()][t.getCol()] = potion;
            placeInChamber(potion, randomStairChamber(playerChamber), floor, map[f]);
        }

        if (f == barrierFloor)
        {
            Tile &barrierSuitTile = floor.popRandomTile(rand() % 5);
            map[f][barrierSuitTile.getRow()][barrierSuitTile.getCol()] = BarrierSuit::CHAR;

            std::vector<Tile *> neighbors = barrierSuitTile.getValidNeighbors();
            Tile &dragonTile = *neighbors[rand() % neighbors.size()];
            map[f][dragonTile.getRow()][dragonTile.getCol()] = Dragon::CHAR;
            dragonCount++;
        }

        for (int i = 0; i < GameModel::ENEMIES_PER_FLOOR; i++)
        {
            char treasure = Randomizer<char>::determineRandom(TREASURE_SPAWN_WEIGHTS);
            Tile &t = floor.popRandomTile(rand() % 5);
            if (treasure == '9')
            {
                std::vector<Tile *> neighbors = t.getValidNeighbors();
                Tile &dragonTile = *neighbors[rand() % neighbors.size()];
                map[f][dragonTile.getRow()][dragonTile.getCol()] = Dragon::CHAR;
                dragonCount++;
            }
            map[f][t.getRow()][t.getCol()] = treasure;
        }

        for (int i = 0; i < GameModel::ENEMIES_PER_FLOOR; i++)
        {
            placeInChamber(Randomizer<char>::determineRandom(ENEMY_SPAWN_WEIGHTS), rand() % 5, floor, map[f]);
        }
    }

    createFloorsFromString(map, std::move(player), onCompassUsed, onStairsUsed, gameLogic);
}

void GameModel::placeInChamber(char c, int chamber, Floor &floor, std::string (&map)[Floor::FLOOR_ROWS])
{
    Tile &t = floor.popRandomTile(chamber);
    map[t.getRow()][t.getCol()] = c;
}

std::unique_ptr<Enemy> GameModel::instantiateEnemy(char enemy, Tile *t, std::unique_ptr<Compass> &compass, Observer *gameLogic)
{
    std::unique_ptr<Enemy> e;
    switch (enemy)
    {
    case Vampire::CHAR:
        e = std::make_unique<Vampire>(t, compass ? std::move(compass) : nullptr);
        break;
    case Werewolf::CHAR:
        e = std::make_unique<Werewolf>(t, compass ? std::move(compass) : nullptr);
        break;
    case Goblin::CHAR:
        e = std::make_unique<Goblin>(t, compass ? std::move(compass) : nullptr);
        break;
    case Merchant::CHAR:
        if (compass)
        {
            e = std::make_unique<Merchant>(t, compass ? std::move(compass) : nullptr);
        }
        else
        {
            std::unique_ptr<Treasure> merchantLoot = std::make_unique<Treasure>(TreasureType::MerchantsHoard, [this](int g)
                                                                                { this->player->collectGold(g); });
            merchantLoot->attach(gameLogic);
            e = std::make_unique<Merchant>(t, std::move(merchantLoot));
        }
        break;
    case Phoenix::CHAR:
        e = std::make_unique<Phoenix>(t, compass ? std::move(compass) : nullptr);
        break;
    case Troll::CHAR:
        e = std::make_unique<Troll>(t, compass ? std::move(compass) : nullptr);
    }
    return e;
}

void GameModel::createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS], std::unique_ptr<Player> player, std::function<void()> onCompassPickup, std::function<void()> onStairsUsed, Observer *gameLogic)
{
    for (int f = 0; f < 5; f++)
    {
        int compassIdx = rand() % 20;
        int enemyCount = 0;
        std::cout << "COMPASS IDX " << compassIdx << std::endl;
        std::vector<std::tuple<Tile &, int, int>> dragons;

        std::unique_ptr<Compass> compass = std::make_unique<Compass>(onCompassPickup);
        compass->attach(gameLogic);

        Player *playerPtr = player.get();
        for (int r = 0; r < Floor::FLOOR_ROWS; r++)
        {
            for (int c = 0; c < Floor::FLOOR_COLS; c++)
            {
                Tile &t = floors[f].getTile(r, c);
                std::unique_ptr<Entity> d = nullptr;
                switch (map[f][r][c])
                {
                case Player::CHAR:
                    startTiles[f] = &t;
                    if (f == currentFloor)
                    {
                        d = std::move(player);
                        currentTile = &t;
                    }
                    break;
                case Stairway::CHAR:
                {
                    std::unique_ptr<Stairway> s = std::make_unique<Stairway>(onStairsUsed);
                    stairs[f] = s.get();
                    d = std::move(s);
                    break;
                }
                case Compass::CHAR:
                    // if (compassIdx < enemyCount)
                    // {
                    d = std::move(compass);
                    compassIdx = -1;
                    // }
                    break;
                case Vampire::CHAR:
                case Werewolf::CHAR:
                case Goblin::CHAR:
                case Merchant::CHAR:
                case Phoenix::CHAR:
                case Troll::CHAR:
                {
                    std::unique_ptr<Compass> comp = compassIdx == enemyCount ? std::move(compass) : nullptr;
                    d = instantiateEnemy(map[f][r][c], &t, comp, gameLogic);
                    enemyCount++;
                    break;
                }
                case Dragon::CHAR:
                {
                    int treasurer = 0;
                    int treasurec = 0;
                    for (int i = 0; i < Tile::NUM_NEIGHBORS; i++)
                    {
                        int nr = t.getRow();
                        int nc = t.getCol();
                        Floor::directionToCoordinate(nr, nc, i);
                        if (Floor::inBounds(nr, nc))
                        {
                            if (map[f][nr][nc] == '9' || map[f][nr][nc] == '8')
                            {

                                treasurer = nr;
                                treasurec = nc;
                            }
                        }
                    }

                    dragons.push_back(std::tuple<Tile &, int, int>{t, treasurer, treasurec});
                    break;
                }
                case '0':
                    d = std::make_unique<StatPotion>(*playerPtr, StatType::Health, 10);
                    break;
                case '1':
                    d = std::make_unique<StatPotion>(*playerPtr, StatType::Attack, 10);
                    break;
                case '2':
                    d = std::make_unique<StatPotion>(*playerPtr, StatType::Defense, 10);
                    break;
                case '3':
                    d = std::make_unique<StatPotion>(*playerPtr, StatType::Health, -10);
                    break;
                case '4':
                    d = std::make_unique<StatPotion>(*playerPtr, StatType::Attack, -10);
                    break;
                case '5':
                    d = std::make_unique<StatPotion>(*playerPtr, StatType::Defense, -10);
                    break;
                case '6':
                case '7':
                    TreasureType t;
                    switch (map[f][r][c])
                    {
                    case '6':
                        t = TreasureType::NormalTreasure;
                        break;
                    case '7':
                        t = TreasureType::SmallHoard;
                        break;
                    }
                    d = std::make_unique<Treasure>(t, [this](int g)
                                                   { this->player->collectGold(g); });
                    break;
                case '8':
                case '9':
                    d = std::make_unique<DragonHoard>(TreasureType::DragonHoard, [this](int g)
                                                      { this->player->collectGold(g); });
                    break;
                default:
                    continue;
                    break;
                }
                if (d != nullptr)
                {
                    d->attach(gameLogic);
                }

                t.setUpperDrawable(std::move(d));
            }
        }

        for (std::tuple<Tile &, int, int> dragonData : dragons)
        {
            Tile &t = std::get<0>(dragonData);
            int treasurer = std::get<1>(dragonData);
            int treasurec = std::get<2>(dragonData);
            ProtectedTreasure *pt = dynamic_cast<ProtectedTreasure *>(floors[f].getTile(treasurer, treasurec).getUpper());
            std::unique_ptr<Dragon> d = std::make_unique<Dragon>(&t, compassIdx == enemyCount ? std::move(compass) : nullptr, pt, treasurer, treasurec);
            t.setUpperDrawable(std::move(d));
            enemyCount++;
        }
    }
}

Floor &GameModel::getCurrentFloor()
{
    return floors[currentFloor];
}

int GameModel::randomStairChamber(int playerChamber)
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