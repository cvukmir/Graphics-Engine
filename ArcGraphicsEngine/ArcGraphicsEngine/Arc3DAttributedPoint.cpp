#include "Arc3DAttributedPoint.h"


// Constructor/Destructor(s) //

Arc3DAttributedPoint::Arc3DAttributedPoint()
	: _opacity(0.0)
	, _s      (0.0)
	, _t      (0.0)
	, _weight (0.0)
{
}

Arc3DAttributedPoint::Arc3DAttributedPoint(const Arc3DPointH& point)
	: _opacity(0.0)
	, _position(point)
	, _s(0.0)
	, _t(0.0)
	, _weight(0.0)
{
}

Arc3DAttributedPoint::Arc3DAttributedPoint(const Arc3DPoint& point)
	: _opacity(0.0)
	, _position(point)
	, _s(0.0)
	, _t(0.0)
	, _weight(0.0)
{
}

Arc3DAttributedPoint::Arc3DAttributedPoint(const Arc3DPoint& point, const ArcColor& color)
	: _opacity(0.0)
	, _position(point)
	, _s(0.0)
	, _t(0.0)
	, _weight(0.0)
{
	_color = color;
}

Arc3DAttributedPoint::~Arc3DAttributedPoint()
{
}


// Public Properties //

void              Arc3DAttributedPoint::color(const ArcColor& value)       { _color = value; }
const ArcColor&   Arc3DAttributedPoint::color() const                      { return _color;  }

void              Arc3DAttributedPoint::opacity(const double value)        { _opacity = value; }
const double      Arc3DAttributedPoint::opacity() const                    { return _opacity;  }

void              Arc3DAttributedPoint::position(const Arc3DPointH& value) { _position = value; }
const Arc3DPointH Arc3DAttributedPoint::position() const                   { return _position; }

void              Arc3DAttributedPoint::textureS(const double value)       { _s = value; }
const double      Arc3DAttributedPoint::textureS() const                   { return _s;  }

void              Arc3DAttributedPoint::textureT(const double value)       { _t = value; }
const double      Arc3DAttributedPoint::textureT() const                   { return _t;  }

void              Arc3DAttributedPoint::vector(const ArcVector& value)     { _vector = value; }
const ArcVector&  Arc3DAttributedPoint::vector() const                     { return _vector;  }

void              Arc3DAttributedPoint::weight(const double value)         { _weight = value; }
const double      Arc3DAttributedPoint::weight() const                     { return _weight;  }


// Public Methods - Overload //

void Arc3DAttributedPoint::operator=(const Arc3DAttributedPoint& rhs)
{
	this->_color    = rhs._color;
	this->_opacity  = rhs._opacity;
	this->_position = rhs._position;
	this->_s        = rhs._s;
	this->_t        = rhs._t;
	this->_vector   = rhs._vector;
	this->_weight   = rhs._weight;
}

bool Arc3DAttributedPoint::operator==(const Arc3DAttributedPoint& rhs)
{
	return this->_color    == rhs._color
		&& this->_opacity  == rhs._opacity
		&& this->_position == rhs._position
		&& this->_s        == rhs._s
		&& this->_t        == rhs._t
		&& this->_vector   == rhs._vector
		&& this->_weight   == rhs._weight;
}

bool Arc3DAttributedPoint::operator!=(const Arc3DAttributedPoint& rhs)
{
	return !(*this == rhs);
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator-(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._position = this->_position - rhs._position;
	newPoint._color    = this->_color    - rhs._color;
	newPoint._vector   = this->_vector   - rhs._vector;

	newPoint._opacity = this->_opacity - rhs._opacity;
	newPoint._s       = this->_s       - rhs._s;
	newPoint._t       = this->_t       - rhs._t;
	newPoint._weight  = this->_weight  - rhs._weight;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator/(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._position = this->_position / rhs._position;
	newPoint._color    = this->_color    / rhs._color;
	newPoint._vector   = this->_vector   / rhs._vector;

	newPoint._opacity = this->_opacity / rhs._opacity;
	newPoint._s       = this->_s       / rhs._s;
	newPoint._t       = this->_t       / rhs._t;
	newPoint._weight  = this->_weight  / rhs._weight;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator*(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._position = this->_position * rhs._position;
	newPoint._color    = this->_color    * rhs._color;
	newPoint._vector   = this->_vector   * rhs._vector;

	newPoint._opacity = this->_opacity * rhs._opacity;
	newPoint._s       = this->_s       * rhs._s;
	newPoint._t       = this->_t       * rhs._t;
	newPoint._weight  = this->_weight  * rhs._weight;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator+(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._position = this->_position + rhs._position;
	newPoint._color    = this->_color    + rhs._color;
	newPoint._vector   = this->_vector   + rhs._vector;

	newPoint._opacity = this->_opacity + rhs._opacity;
	newPoint._s       = this->_s       + rhs._s;
	newPoint._t       = this->_t       + rhs._t;
	newPoint._weight  = this->_weight  + rhs._weight;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator/(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._position = this->_position / rhs;
	newPoint._color    = this->_color    / rhs;
	newPoint._vector   = this->_vector   / rhs;

	newPoint._opacity = this->_opacity / rhs;
	newPoint._s       = this->_s       / rhs;
	newPoint._t       = this->_t       / rhs;
	newPoint._weight  = this->_weight  / rhs;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator*(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._position = this->_position * rhs;
	newPoint._color    = this->_color    * rhs;
	newPoint._vector   = this->_vector   * rhs;

	newPoint._opacity = this->_opacity * rhs;
	newPoint._s       = this->_s       * rhs;
	newPoint._t       = this->_t       * rhs;
	newPoint._weight  = this->_weight  * rhs;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator-(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._position = this->_position - rhs;
	newPoint._color    = this->_color    - rhs;
	newPoint._vector   = this->_vector   - rhs;

	newPoint._opacity = this->_opacity - rhs;
	newPoint._s       = this->_s       - rhs;
	newPoint._t       = this->_t       - rhs;
	newPoint._weight  = this->_weight  - rhs;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator+(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._position = this->_position + rhs;
	newPoint._color    = this->_color    + rhs;
	newPoint._vector   = this->_vector   + rhs;

	newPoint._opacity = this->_opacity + rhs;
	newPoint._s       = this->_s       + rhs;
	newPoint._t       = this->_t       + rhs;
	newPoint._weight  = this->_weight  + rhs;

	return newPoint;
}


// Public Methods - Static //

Arc3DAttributedPoint Arc3DAttributedPoint::interpolateTo(const Arc3DAttributedPoint& startPoint, const Arc3DAttributedPoint& endPoint, const double alpha)
{
	Arc3DAttributedPoint newPoint;

	newPoint._position = Arc3DPointH::interpolateTo(startPoint._position, endPoint._position, alpha);
	newPoint._color    =    ArcColor::interpolateTo(startPoint._color,    endPoint._color,    alpha);
	newPoint._vector   =   ArcVector::interpolateTo(startPoint._vector,   endPoint._vector,   alpha);

	newPoint._opacity = startPoint._opacity + ((endPoint._opacity - startPoint._opacity) * alpha);
	newPoint._s       = startPoint._s       + ((endPoint._s       - startPoint._s)       * alpha);
	newPoint._t       = startPoint._t       + ((endPoint._t       - startPoint._t)       * alpha);
	newPoint._weight  = startPoint._weight  + ((endPoint._weight  - startPoint._weight)  * alpha);

	return newPoint;
}


// Public Methods //

void Arc3DAttributedPoint::selfInterpolateTo(const Arc3DAttributedPoint& point, const double alpha)
{
	this->_position.selfInterpolateTo(point._position, alpha);
	this->_color.   selfInterpolateTo(point._color,    alpha);
	this->_vector.  selfInterpolateTo(point._vector,   alpha);

	this->_opacity += ((point._opacity - this->_opacity) * alpha);
	this->_s       += ((point._s       - this->_s)       * alpha);
	this->_t       += ((point._t       - this->_t)       * alpha);
	this->_weight  += ((point._weight  - this->_weight)  * alpha);
}

void Arc3DAttributedPoint::updatePosition(const Arc3DPoint& point)
{
	_position.updatePosition(point);
}

void Arc3DAttributedPoint::updatePosition(const Arc3DPointH& point)
{
	_position.updatePosition(point);
}
