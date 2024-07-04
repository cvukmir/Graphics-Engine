// ArcFramework
#include "ArcColor.h"
#include "ArcTypedefs.h"
#include "ArcMath.h"


// Constructor/Destructor(s) //

const double MAX_COLOR_VAL = 255.999;

ArcColor::ArcColor()
	: _blue (1.0)
	, _green(1.0)
	, _red  (1.0)
{
}

ArcColor::ArcColor(const uint color)
{
	_blue  = ArcMath::clamp(static_cast<double>(getBlueComponent( color)) / MAX_COLOR_VAL, 0.0, 1.0);
	_green = ArcMath::clamp(static_cast<double>(getGreenComponent(color)) / MAX_COLOR_VAL, 0.0, 1.0);
	_red   = ArcMath::clamp(static_cast<double>(getRedComponent(  color)) / MAX_COLOR_VAL, 0.0, 1.0);
}

ArcColor::ArcColor(const double red, const double green, const double blue)
	: _blue (blue)
	, _green(green)
	, _red  (red)
{
}

ArcColor::~ArcColor()
{
}


// Overload(s) //

void ArcColor::operator=(const ArcColor& rhs)
{
	this->_blue  = rhs._blue;
	this->_green = rhs._green;
	this->_red   = rhs._red;
}

bool ArcColor::operator==(const ArcColor& rhs) const
{
	return this->_blue  == rhs._blue
		&& this->_green == rhs._green
		&& this->_red   == rhs._red;
}

ArcColor ArcColor::operator-(const ArcColor& rhs) const
{
	return ArcColor(this->_red   - rhs._red,
		            this->_green - rhs._green,
		            this->_blue  - rhs._blue);
}

ArcColor ArcColor::operator/(const ArcColor& rhs) const
{
	return ArcColor(this->_red   / rhs._red,
		            this->_green / rhs._green,
		            this->_blue  / rhs._blue);
}

ArcColor ArcColor::operator+(const ArcColor& rhs) const
{
	return ArcColor(this->_red   + rhs._red,
		            this->_green + rhs._green,
		            this->_blue  + rhs._blue);
}

ArcColor ArcColor::operator*(const ArcColor& rhs) const
{
	return ArcColor(this->_red   * rhs._red,
		            this->_green * rhs._green,
		            this->_blue  * rhs._blue);
}

ArcColor ArcColor::operator/(const double rhs) const
{
	return ArcColor(this->_red   / rhs,
		            this->_green / rhs,
		            this->_blue  / rhs);
}

ArcColor ArcColor::operator*(const double rhs) const
{
	return ArcColor(this->_red   * rhs,
		            this->_green * rhs,
		            this->_blue  * rhs);
}

ArcColor ArcColor::operator-(const double rhs) const
{
	return ArcColor(this->_red   - rhs,
		            this->_green - rhs,
		            this->_blue  - rhs);
}

ArcColor ArcColor::operator+(const double rhs) const
{
	return ArcColor(this->_red   + rhs,
		            this->_green + rhs,
		            this->_blue  + rhs);
}


// Public Properties //

void         ArcColor::blue(const double value)  { _blue = value; }
const double ArcColor::blue() const              { return _blue;  }

void         ArcColor::green(const double value) { _green = value; }
const double ArcColor::green() const             { return _green;  }

void         ArcColor::red(const double value)   { _red = value; }
const double ArcColor::red() const               { return _red;  }


// Static Properties //

uint ArcColor::getBlueComponent(const uint value)  { return (value & 0x000000FFU); }

uint ArcColor::getGreenComponent(const uint value) { return (value & 0x0000FF00U) >> 8U; }

uint ArcColor::getRedComponent(const uint value)   { return (value & 0x00FF0000U) >> 16U; }


// Public Methods - Static //

ArcColor ArcColor::interpolateTo(const ArcColor& startColor, const ArcColor& endColor, const double alpha)
{
	return ArcColor(startColor._red   + (alpha * (endColor._red   - startColor._red)),
		            startColor._green + (alpha * (endColor._green - startColor._green)),
		            startColor._blue  + (alpha * (endColor._blue  - startColor._blue)));
}


// Public Methods //

void ArcColor::selfInterpolateTo(const ArcColor& color, const double alpha)
{
	_red   = _red   + (alpha * (color._red   - _red));
	_green = _green + (alpha * (color._green - _green));
	_blue  = _blue  + (alpha * (color._blue  - _blue));
}

uint ArcColor::colorToUint() const
{
	//(Max – E) * x --> (256 - .001) * colorVal
	const uint redComponent   = static_cast<uint>(MAX_COLOR_VAL * _red)   << 16;
	const uint greenComponent = static_cast<uint>(MAX_COLOR_VAL * _green) << 8;
	const uint blueComponent  = static_cast<uint>(MAX_COLOR_VAL * _blue);

	return redComponent | greenComponent | blueComponent;
}


// Private Methods //