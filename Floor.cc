#include "Floor.h"
#include "FloorTile.h"
#include "VertWall.h"
#include "HorizWall.h"
#include "Door.h"
#include "PassageWay.h"
#include "EmptyTile.h"
#include <random>

#include <memory>

static const std::string defaultLayout[Floor::FLOOR_ROWS] = {
    "|-----------------------------------------------------------------------------|",
    "|                                                                             |",
    "| |--------------------------|        |-----------------------|               |",
    "| |..........................|        |.......................|               |",
    "| |..........................+########+.......................|-------|       |",
    "| |..........................|   #    |...............................|--|    |",
    "| |..........................|   #    |..................................|--| |",
    "| |----------+---------------|   #    |----+----------------|...............| |",
    "|            #                 #############                |...............| |",
    "|            #                 #     |-----+------|         |...............| |",
    "|            #                 #     |............|         |...............| |",
    "|            ###################     |............|   ######+...............| |",
    "|            #                 #     |............|   #     |...............| |",
    "|            #                 #     |-----+------|   #     |--------+------| |",
    "|  |---------+-----------|     #           #          #              #        |",
    "|  |.....................|     #           #          #         |----+------| |",
    "|  |.....................|     ########################         |...........| |",
    "|  |.....................|     #           #                    |...........| |",
    "|  |.....................|     #    |------+--------------------|...........| |",
    "|  |.....................|     #    |.......................................| |",
    "|  |.....................+##########+.......................................| |",
    "|  |.....................|          |.......................................| |",
    "|  |---------------------|          |---------------------------------------| |",
    "|                                                                             |",
    "|-----------------------------------------------------------------------------|"};

Floor::Floor() : tiles{std::vector<std::vector<Tile>>{}}
{
    for (int r = 0; r < Floor::FLOOR_ROWS; r++)
    {
        tiles.push_back(std::vector<Tile>{});
        for (int c = 0; c < Floor::FLOOR_COLS; c++)
        {
            std::unique_ptr<Drawable> d;
            switch (defaultLayout[r][c])
            {
            case '.':
                d = std::make_unique<FloorTile>();
                break;
            case '|':
                d = std::make_unique<VertWall>();
                break;
            case '-':
                d = std::make_unique<HorizWall>();
                break;
            case '+':
                d = std::make_unique<Door>();
                break;
            case '#':
                d = std::make_unique<PassageWay>();
                break;
            case ' ':
                d = std::make_unique<EmptyTile>();
            }

            tiles[r].push_back(Tile{r, c, std::move(d), nullptr});
        }
    }

    for (int r = 0; r < Floor::FLOOR_ROWS; r++)
    {
        for (int c = 0; c < Floor::FLOOR_COLS; c++)
        {
            Tile *neighbors[Tile::NUM_NEIGHBORS];

            for (int i = 0; i < Tile::NUM_NEIGHBORS; i++)
            {
                int newR = r, newC = c;

                directionToCoordinate(newR, newC, i);

                if (inBounds(newR, newC))
                {
                    neighbors[i] = &tiles[newR][newC];
                }
                else
                {
                    neighbors[i] = nullptr;
                }
            }

            tiles[r][c].setNeighbors(neighbors);
        }
    }

    setupChambers();
}

Tile &Floor::getTile(int r, int c)
{
    return tiles[r][c];
}

Tile &Floor::randomTile(int chamber)
{
    int idx = rand() % chambers[chamber].size();
    auto it = chambers[chamber].begin();
    for (int i = 0; i < idx; i++)
    {
        ++it;
    }

    Tile *t = *it;
    return *t;
}

void Floor::RemoveTileFromChamber(Tile *t, int chamber)
{
    chambers[chamber].erase(t);
}

void Floor::directionToCoordinate(int &r, int &c, int dir)
{
    switch (dir)
    {
    case 0:
        r -= 1;
        return;
    case 1:
        r -= 1;
        c += 1;
        return;
    case 2:
        c += 1;
        return;
    case 3:
        r += 1;
        c += 1;
        return;
    case 4:
        r += 1;
        return;
    case 5:
        r += 1;
        c -= 1;
        return;
    case 6:
        c -= 1;
        return;
    case 7:
        r -= 1;
        c -= 1;
        return;
    }
}

bool Floor::inBounds(int r, int c)
{
    return r >= 0 && r < Floor::FLOOR_ROWS && c >= 0 && c < Floor::FLOOR_COLS;
}

void Floor::setupChambers()
{

    for (int i = 0; i < 5; i++)
    {
        chambers.push_back(std::set<Tile *>{});
    }

    // Add tiles refs to chamber 1:

    for (int r = 3; r <= 6; r++)
    {
        for (int c = 3; c <= 28; c++)
        {
            chambers[0].insert(&tiles[r][c]);
        }
    }

    for (int r = 15; r <= 21; r++)
    {
        for (int c = 4; c <= 24; c++)
        {
            chambers[1].insert(&tiles[r][c]);
        }
    }

    for (int r = 16; r <= 18; r++)
    {
        for (int c = 65; c <= 75; c++)
        {
            chambers[2].insert(&tiles[r][c]);
        }
    }

    for (int r = 19; r <= 21; r++)
    {
        for (int c = 37; c <= 75; c++)
        {
            chambers[2].insert(&tiles[r][c]);
        }
    }

    for (int r = 3; r <= 6; r++)
    {
        for (int c = 39; c <= 61; c++)
        {
            chambers[3].insert(&tiles[r][c]);
        }
    }

    for (int r = 5; r <= 6; r++)
    {
        for (int c = 62; c <= 69; c++)
        {
            chambers[3].insert(&tiles[r][c]);
        }
    }

    for (int r = 6; r <= 6; r++)
    {
        for (int c = 69; c <= 72; c++)
        {
            chambers[3].insert(&tiles[r][c]);
        }
    }

    for (int r = 7; r <= 12; r++)
    {
        for (int c = 61; c <= 75; c++)
        {
            chambers[3].insert(&tiles[r][c]);
        }
    }

    for (int r = 10; r <= 12; r++)
    {
        for (int c = 38; c <= 49; c++)
        {
            chambers[4].insert(&tiles[r][c]);
        }
    }
}