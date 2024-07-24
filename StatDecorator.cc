#include "StatDecorator.h"

StatDecorator::~StatDecorator()
{
   delete next;
}