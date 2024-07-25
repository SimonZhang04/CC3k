#include "GameModel.h"
#include "Dragon.h"
#include "Dwarf.h"
#include "Elf.h"
#include "Goblin.h"
#include "Human.h"
#include "Merchant.h"
#include "Orc.h"
#include "Phoenix.h"
#include "Troll.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Treasure.h"
#include "Potion.h"
#include <exception>

GameModel::GameModel() : currentFloor{0}, floors{std::vector<Floor>{}}
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

void GameModel::createFloorsFromString(std::string map[5][Floor::FLOOR_ROWS], std::unique_ptr<Player> player, std::function<void()> onCompassPickup)
{
    for (int f = 0; f < 5; f++)
    {
        int compassIdx = rand() % 20;
        int enemyCount = 0;
        std::unique_ptr<Compass> compass = std::make_unique<Compass>(onCompassPickup);
        for (int r = 0; r < Floor::FLOOR_ROWS; r++)
        {
            for (int c = 0; c < Floor::FLOOR_COLS; c++)
            {
                Tile &t = floors[f].getTile(r, c);
                std::unique_ptr<Drawable> d = nullptr;
                switch (map[f][r][c])
                {
                case Player::CHAR:
                    d = std::move(player);
                    if (f == currentFloor)
                    {
                        currentTile = &t;
                    }
                    break;
                case Vampire::CHAR:
                    d = std::make_unique<Vampire>(compassIdx == enemyCount ? std::move(compass) : nullptr);
                    enemyCount++;
                    break;
                case Werewolf::CHAR:
                    d = std::make_unique<Werewolf>(compassIdx == enemyCount ? std::move(compass) : nullptr);
                    enemyCount++;
                    break;
                case Goblin::CHAR:
                    d = std::make_unique<Goblin>(compassIdx == enemyCount ? std::move(compass) : nullptr);
                    enemyCount++;
                    break;
                case Merchant::CHAR:
                    // std::unique_ptr<Drawable> xd = std::make_unique<Treasure>(12, test);
                    if (compassIdx == enemyCount)
                    {
                        d = std::make_unique<Merchant>(std::move(compass));
                    }
                    else
                    {
                        d = std::make_unique<Merchant>(std::make_unique<Treasure>(TreasureType::MerchantsHoard, [this](int g)
                                                                                  { this->player->collectGold(g); }));
                    }
                    enemyCount++;
                    break;
                case Dragon::CHAR:
                    d = std::make_unique<Dragon>(compassIdx == enemyCount ? std::move(compass) : nullptr);
                    enemyCount++;
                    break;
                case Phoenix::CHAR:
                    d = std::make_unique<Phoenix>(compassIdx == enemyCount ? std::move(compass) : nullptr);
                    enemyCount++;
                    break;
                case Troll::CHAR:
                    d = std::make_unique<Troll>(compassIdx == enemyCount ? std::move(compass) : nullptr);
                    enemyCount++;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                    // Potions
                    d = std::make_unique<Potion>([this](PotionType p)
                                                 { this->player->usePotion(p, 10); }, PotionType::BoostAtk);
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
                    // Protected Treasure
                    break;
                default:
                    continue;
                    break;
                }

                t.setUpperDrawable(std::move(d));
            }
        }
    }
}

Floor &GameModel::getCurrentFloor()
{
    return floors[currentFloor];
}