#include "GameLogic.h"

int main(int argc, char *argv[])
{
    GameLogic gl;

    std::string floorFile = "";
    if (argc > 1)
    {
        floorFile = argv[1];
    }

    gl.playGame(floorFile);
    return 0;
}