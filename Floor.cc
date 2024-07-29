#include "Floor.h"
#include "Door.h"
#include "Drawable.h"
#include "EmptyTile.h"
#include "FloorTile.h"
#include "HorizWall.h"
#include "PassageWay.h"
#include "Potion.h"
#include "VertWall.h"
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

const std::string Floor::DEFAULT_LAYOUT[Floor::FLOOR_ROWS] = {
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

Floor::Floor() : tiles{std::vector<std::vector<Tile>>{}}, chambers{std::vector<std::set<Tile *>>{}}
{
    for (int r = 0; r < Floor::FLOOR_ROWS; r++)
    {
        tiles.push_back(std::vector<Tile>{});
        for (int c = 0; c < Floor::FLOOR_COLS; c++)
        {
            std::unique_ptr<Drawable> lower;
            std::unique_ptr<Drawable> upper = nullptr;
            switch (DEFAULT_LAYOUT[r][c])
            {
            case '.':
                lower = std::make_unique<FloorTile>();
                break;
            case '|':
                lower = std::make_unique<VertWall>();
                upper = std::make_unique<VertWall>();
                break;
            case '-':
                lower = std::make_unique<HorizWall>();
                upper = std::make_unique<HorizWall>();
                break;
            case '+':
                lower = std::make_unique<Door>();
                break;
            case '#':
                lower = std::make_unique<PassageWay>();
                break;
            case ' ':
                lower = std::make_unique<EmptyTile>();
                upper = std::make_unique<EmptyTile>();
            }

            tiles[r].push_back(Tile{r, c, std::move(lower), std::move(upper)});
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

std::vector<Tile *> Floor::getSurroundingTiles(int r, int c)
{
    Tile &t = getTile(r, c);
    std::vector<Tile *> surroundingTiles;
    for (int i = 0; i < Tile::NUM_NEIGHBORS; i++)
    {
        int nr = t.getRow();
        int nc = t.getCol();
        directionToCoordinate(nr, nc, i);
        if (inBounds(nr, nc))
        {
            surroundingTiles.push_back(&tiles[nr][nc]);
        }
    }
    return surroundingTiles;
}

bool Floor::surroundingTilesContains(int r, int c, std::unordered_set<char> charsToCheck)
{
    for (Tile *t : getSurroundingTiles(r, c))
    {
        if (charsToCheck.count(tiles[t->getRow()][t->getCol()].draw()))
        {
            return true;
        }
    }
    return false;
}

Tile &Floor::getTile(int r, int c)
{
    return tiles[r][c];
}

Enemy *Floor::checkForEnemy(int r, int c)
{
    Drawable *d = getTile(r, c).getUpper();
    return dynamic_cast<Enemy *>(d);
}

Potion *Floor::checkForPotion(int r, int c)
{
    Drawable *d = getTile(r, c).getUpper();
    return dynamic_cast<Potion *>(d);
}

Tile &Floor::popRandomTile(int chamber)
{

    Tile *t = &peekRandomTile(chamber);
    removeTileFromChamber(t, chamber);
    return *t;
}

Tile &Floor::peekRandomTile(int chamber)
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

void Floor::replaceEntity(int r, int c, std::unique_ptr<Drawable> newUpper)
{
    tiles[r][c].setUpperDrawable(std::move(newUpper));
}

void Floor::removeTileFromChamber(Tile *t, int chamber)
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