#include "Stat.h"

class StatViewer : public Stat
{
   int *baseStat;

public:
   StatViewer(int *baseStat) : baseStat{baseStat} {}
   int getStat() const override;
};