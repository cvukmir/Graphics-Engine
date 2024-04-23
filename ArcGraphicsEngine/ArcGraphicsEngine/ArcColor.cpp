// ArcFramework
#include "ArcColor.h"
#include "ArcTypedefs.h"


// Constructor/Destructor(s) //

ArcColor::ArcColor()
	: _color(ArcColor::WHITE)
{
}

ArcColor::ArcColor(const uint color)
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


// Overload(s) //

void ArcColor::operator=(const ArcColor& rhs) const
{
	this->_color == rhs._color;
}

bool ArcColor::operator==(const ArcColor& rhs) const
{
	return this->_color == rhs._color;
}

ArcColor ArcColor::operator-(const ArcColor& rhs) const
{
	return this->_color - rhs._color;
}

ArcColor ArcColor::operator/(const ArcColor& rhs) const
{
	return this->_color / rhs._color;
}

ArcColor ArcColor::operator+(const ArcColor& rhs) const
{
	return this->_color + rhs._color;
}

ArcColor ArcColor::operator*(const ArcColor& rhs) const
{
	return this->_color * rhs._color;
}

ArcColor ArcColor::operator/(const double rhs) const
{
	return this->_color / rhs;
}

ArcColor ArcColor::operator*(const double rhs) const
{
	return this->_color * rhs;
}

ArcColor ArcColor::operator-(const double rhs) const
{
	return this->_color - rhs;
}

ArcColor ArcColor::operator+(const double rhs) const
{
	return this->_color + rhs;
}


// Public Properties //

void       ArcColor::color(const uint value) { _color = value; }
const uint ArcColor::color() const           { return _color; }


// Static Properties //

uint ArcColor::getBlueComponent(const uint value)  { return (value & 0x000000FFU); }

uint ArcColor::getGreenComponent(const uint value) { return (value & 0x0000FF00U) >> 8U; }

uint ArcColor::getRedComponent(const uint value)   { return (value & 0x00FF0000U) >> 16U; }


// Public Methods - Static //

ArcColor ArcColor::interpolateTo(const ArcColor& startColor, const ArcColor& endColor, const double alpha)
{
	return ArcColor(startColor._color + (alpha * (endColor._color - startColor._color)));
}

uint ArcColor::colorFromFloat(const float red, const float green, const float blue)
{
	//(Max – E)* x
	const float max = 254.999f;

	const uint redComponent   = static_cast<uint>(max * red) << 16;
	const uint blueComponent  = static_cast<uint>(max * green) << 8;
	const uint greenComponent = static_cast<uint>(max * blue);

	return redComponent | blueComponent | greenComponent;
}


// Public Methods //

void ArcColor::selfInterpolateTo(const ArcColor& color, const double alpha)
{
	_color = _color + (alpha * (color._color - _color));
}


// Private Methods //