#ifndef STATVIEWER
#define STATVIEWER

#include "Stat.h"

class StatViewer : public Stat
{
   const int &baseStat;

public:
   StatViewer(const int &baseStat) : Stat{}, baseStat{baseStat} {}
   int getStat() const override;
};

#endif