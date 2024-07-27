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

void GameModel::generateFloor(Floor &f, std::function<void()> onCompassPickup)
{
    int playerChamber = rand() % 5;
    Tile &t = f.randomTile(playerChamber);
    f.RemoveTileFromChamber(&t, playerChamber);

    int stairChamber = randomStairChamber(playerChamber);
    // deal with this

    // curFloor

    std::unique_ptr<Compass> compass = std::make_unique<Compass>(onCompassPickup);

    // TODO: consider just generating a map using strings and re-using generation from text

    // for (int i = 0; i < GameModel::ENEMIES_PER_FLOOR; i++)
    // {
    //     char enemy = Randomizer<char>::determineRandom(ENEMY_SPAWN_WEIGHTS);
    //     int randChamber = rand() % 5;
    //     Tile &t = f.randomTile(randChamber);
    //     std::unique_ptr<Enemy> e = instantiateEnemy(enemy, t, )
    // }
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

                if (f == 0 && compassIdx == enemyCount)
                { // TODO: REMOVE
                    std::cout << r << " " << c << std::endl;
                }
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
            std::unique_ptr<Dragon> d = std::make_unique<Dragon>(&t, compassIdx == enemyCount ? std::move(compass) : nullptr, pt);
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