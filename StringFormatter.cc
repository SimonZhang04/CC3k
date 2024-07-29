#include "StringFormatter.h"

std::string StringFormatter::formatFloat(float f)
{
    std::stringstream ss{};
    ss << std::fixed << std::setprecision(1) << f;
    return ss.str();
}

std::string StringFormatter::formatColor(char c)
{
    Color col = charToColor(c);
    std::string colorCode = "";
    switch (col)
    {
    case Color::None:
        return std::string{c};
    case Color::Red:
        colorCode = "31";
        break;
    case Color::Green:
        colorCode = "32";
        break;
    case Color::Yellow:
        colorCode = "33";
        break;
    case Color::Blue:
        colorCode = "34";
        break;
    case Color::Magenta:
        colorCode = "35";
        break;
    case Color::Cyan:
        colorCode = "36";
        break;
    }
    std::string s = "\033[" + colorCode + "m";
    s += c;
    s += "\033[0m";
    return s;
}

Color StringFormatter::charToColor(char c)
{
    switch (c)
    {
    case Player::CHAR:
        return Color::Green;
    case Compass::CHAR:
    case Stairway::CHAR:
        return Color::Cyan;
    case BarrierSuit::CHAR:
        return Color::Blue;
    case Treasure::CHAR:
        return Color::Yellow;
    case Potion::CHAR:
        return Color::Magenta;
    case Vampire::CHAR:
    case Werewolf::CHAR:
    case Goblin::CHAR:
    case Merchant::CHAR:
    case Phoenix::CHAR:
    case Troll::CHAR:
    case Dragon::CHAR:
        return Color::Red;
    }
    return Color::None;
}