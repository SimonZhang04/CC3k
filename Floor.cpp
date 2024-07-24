#include "Floor.h"
#include "FloorTile.h"
#include "Drawable.h"
#include "VertWall.h"
#include "HorizWall.h"
#include "Door.h"
#include "PassageWay.h"

#include <memory>
Floor::Floor()
{
    for (int r = 0; r < 30; r++)
    {
        tiles.push_back(std::vector<Tile>{79});
        for (int c = 0; c < 79; c++)
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
                d = nullptr;
            }

            tiles[r].push_back(Tile{std::move(d)});
        }
    }
}