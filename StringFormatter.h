#ifndef STRINGFORMATTER
#define STRINGFORMATTER

#include "Color.h"
#include <iomanip>

class StringFormatter
{
public:
    static std::string formatFloat(float f);
    static std::string formatColor(char c);
    static Color charToColor(char c);
};

#endif
