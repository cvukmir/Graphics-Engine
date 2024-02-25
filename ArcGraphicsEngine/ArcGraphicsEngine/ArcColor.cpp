#include "ArcColor.h"

ArcColor::ArcColor()
	: _color(ArcColor::WHITE)
{
}

ArcColor::ArcColor(const unsigned int color)
	: _color(color)
{
}

ArcColor::ArcColor(const float red, const float blue, const float green)
{
	_color = colorFromFloat(red, blue, green);
}

ArcColor::~ArcColor()
{
}

const int ArcColor::colorFromFloat(const float red, const float green, const float blue)
{
	//(Max – E)* x
	const float max = 254.999f;

	const int redComponent   = static_cast<int>(max * red)   << 16;
	const int blueComponent  = static_cast<int>(max * green) << 8;
	const int greenComponent = static_cast<int>(max * blue);

	return redComponent | blueComponent | greenComponent;
}

unsigned int ArcColor::getRedComponent(const unsigned int value)   { return (value & 0x00FF0000) >> 16; }
unsigned int ArcColor::getGreenComponent(const unsigned int value) { return (value & 0x0000FF00) >> 8; }
unsigned int ArcColor::getBlueComponent(const unsigned int value)  { return (value & 0x000000FF); }


void               ArcColor::color(const unsigned int value) { _color = value; }
const unsigned int ArcColor::color() const                   { return _color; }
