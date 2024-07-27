#ifndef STATVIEWER
#define STATVIEWER

#include "Stat.h"
#include <iostream>
class StatViewer : public Stat
{
   const float baseStat;

public:
   StatViewer(const float baseStat) : Stat{}, baseStat{baseStat} {}
   float getStat() const override;
};

#endif