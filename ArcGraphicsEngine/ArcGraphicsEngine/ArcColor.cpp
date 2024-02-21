#include "ArcColor.h"

ArcColor::ArcColor()
	: _color(0x00000000U)
{
}

ArcColor::ArcColor(unsigned int color)
	: _color(color)
{
}

ArcColor::~ArcColor()
{
}

void               ArcColor::color(const unsigned int value) { _color = value; }
const unsigned int ArcColor::color() const                   { return _color; }
