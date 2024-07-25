#ifndef STATVIEWER
#define STATVIEWER

#include "Stat.h"

class StatViewer : public Stat
{
   int *baseStat;

public:
   StatViewer(int *baseStat) : Stat{}, baseStat{baseStat} {}
   int getStat() const override;
};

#endif