#ifndef STATVIEWER
#define STATVIEWER

#include "Stat.h"
#include <functional>
class StatViewer : public Stat
{
   std::function<float()> base;

public:
   StatViewer(std::function<float()> base) : Stat{}, base{std::move(base)} {}
   float getStat() const override;
   std::unique_ptr<Stat> undecorate() override
   {
      return nullptr;
   }
};

#endif