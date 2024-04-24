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
	float r1 = static_cast<float>(  getRedComponent(startColor._color));
	float g1 = static_cast<float>(getGreenComponent(startColor._color));
	float b1 = static_cast<float>( getBlueComponent(startColor._color));

	float r2 = static_cast<float>(  getRedComponent(endColor._color));
	float g2 = static_cast<float>(getGreenComponent(endColor._color));
	float b2 = static_cast<float>( getBlueComponent(endColor._color));
	
	return ArcColor(r1 + (alpha * (r2 - r1)),
		            g1 + (alpha * (g2 - g1)),
		            b1 + (alpha * (b2 - b1))).color();
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
	float r1 = static_cast<float>(  getRedComponent(_color));
	float g1 = static_cast<float>(getGreenComponent(_color));
	float b1 = static_cast<float>( getBlueComponent(_color));

	float r2 = static_cast<float>(  getRedComponent(color._color));
	float g2 = static_cast<float>(getGreenComponent(color._color));
	float b2 = static_cast<float>( getBlueComponent(color._color));

	_color = ArcColor(r1 + (alpha * (r2 - r1)),
		              g1 + (alpha * (g2 - g1)),
		              b1 + (alpha * (b2 - b1))).color();
}


// Private Methods //