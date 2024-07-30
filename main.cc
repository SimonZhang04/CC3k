#include "GameLogic.h"

char *getOption(char **begin, char **end, const std::string &flag)
{
    char **iterator = std::find(begin, end, flag);
    if (iterator != end && ++iterator != end)
    {
        return *iterator;
    }
    return 0;
}

bool hasFlag(char **begin, char **end, const std::string &flag)
{
    return std::find(begin, end, flag) != end;
}

int main(int argc, char *argv[])
{

    std::string floorFile = "";
    bool bonusActive = false;
    if (argc > 1)
    {
        char *map = getOption(argv, argv + argc, "-f");
        if (map)
        {
            floorFile = map;
        }

        char *seed = getOption(argv, argv + argc, "-s");
        if (seed)
        {
            srand(std::stoi(seed));
        }

        bonusActive = hasFlag(argv, argv + argc, "-b");
    }

    GameLogic gl{bonusActive};
    gl.playGame(floorFile);
    return 0;
}
