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

unsigned int ArcColor::getRedComponent(const unsigned int value)   { return (value & 0x00FF0000) >> 16; }
unsigned int ArcColor::getGreenComponent(const unsigned int value) { return (value & 0x0000FF00) >> 8; }
unsigned int ArcColor::getBlueComponent(const unsigned int value)  { return (value & 0x000000FF); }


void               ArcColor::color(const unsigned int value) { _color = value; }
const unsigned int ArcColor::color() const                   { return _color; }
