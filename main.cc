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

int main(int argc, char *argv[])
{
    GameLogic gl;

    std::string floorFile = "";
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
    }
    gl.playGame(floorFile);
    return 0;
}
