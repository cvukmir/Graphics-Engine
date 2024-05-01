#include "Arc3DAttributedPoint.h"


// Constructor/Destructor(s) //

Arc3DAttributedPoint::Arc3DAttributedPoint()
	: _constant(1.0)
	, _opacity (0.0)
	, _s       (0.0)
	, _t       (0.0)
	, _weight  (0.0)
{
}

Arc3DAttributedPoint::Arc3DAttributedPoint(const Arc3DPointH& point)
	: _constant(1.0)
	, _opacity(0.0)
	, _position(point)
	, _s(0.0)
	, _t(0.0)
	, _weight(0.0)
{
}

Arc3DAttributedPoint::Arc3DAttributedPoint(const Arc3DPoint& point)
	: _constant(1.0)
	, _opacity(0.0)
	, _position(point)
	, _s(0.0)
	, _t(0.0)
	, _weight(0.0)
{
}

Arc3DAttributedPoint::Arc3DAttributedPoint(const Arc3DPoint& point, const ArcVector& normalVector)
	: _constant(1.0)
	, _opacity(0.0)
	, _normalVector(normalVector)
	, _position(point)
	, _s(0.0)
	, _t(0.0)
	, _weight(0.0)
{
}

Arc3DAttributedPoint::Arc3DAttributedPoint(const Arc3DPoint& point, const ArcColor& color)
	: _constant(1.0)
	, _color(color)
	, _opacity(0.0)
	, _position(point)
	, _s(0.0)
	, _t(0.0)
	, _weight(0.0)
{
}

Arc3DAttributedPoint::~Arc3DAttributedPoint()
{
}


// Public Properties //

void              Arc3DAttributedPoint::constant(const double value)        { _constant = value; }
const double      Arc3DAttributedPoint::constant() const                    { return _constant;  }

void              Arc3DAttributedPoint::color(const ArcColor& value)       { _color = value; }
const ArcColor&   Arc3DAttributedPoint::color() const                      { return _color;  }
ArcColor&         Arc3DAttributedPoint::colorM()                           { return _color;  }

void              Arc3DAttributedPoint::opacity(const double value)        { _opacity = value; }
const double      Arc3DAttributedPoint::opacity() const                    { return _opacity;  }

void              Arc3DAttributedPoint::position(const Arc3DPointH& value) { _position = value; }
const Arc3DPointH Arc3DAttributedPoint::position() const                   { return _position;  }

void              Arc3DAttributedPoint::textureS(const double value)       { _s = value; }
const double      Arc3DAttributedPoint::textureS() const                   { return _s;  }

void              Arc3DAttributedPoint::textureT(const double value)       { _t = value; }
const double      Arc3DAttributedPoint::textureT() const                   { return _t;  }

void              Arc3DAttributedPoint::normalVector(const ArcVector& value) { _normalVector = value; }
const ArcVector&  Arc3DAttributedPoint::normalVector() const                 { return _normalVector;  }

void              Arc3DAttributedPoint::weight(const double value)         { _weight = value; }
const double      Arc3DAttributedPoint::weight() const                     { return _weight;  }

void              Arc3DAttributedPoint::worldPosition(const Arc3DPoint& value) { _worldPosition = value; }
const Arc3DPoint  Arc3DAttributedPoint::worldPosition() const                  { return _worldPosition;  }


// Public Methods - Overload //

void Arc3DAttributedPoint::operator=(const Arc3DAttributedPoint& rhs)
{
	this->_constant = rhs._constant;
	this->_color    = rhs._color;
	this->_opacity  = rhs._opacity;
	this->_position = rhs._position;
	this->_s        = rhs._s;
	this->_t        = rhs._t;
	this->_normalVector   = rhs._normalVector;
	this->_weight   = rhs._weight;
	this->_worldPosition = rhs._worldPosition;
}

bool Arc3DAttributedPoint::operator==(const Arc3DAttributedPoint& rhs)
{
	return this->_constant      == rhs._constant
		&& this->_color         == rhs._color
		&& this->_opacity       == rhs._opacity
		&& this->_position      == rhs._position
		&& this->_s             == rhs._s
		&& this->_t             == rhs._t
		&& this->_normalVector  == rhs._normalVector
		&& this->_weight        == rhs._weight
		&& this->_worldPosition == rhs._worldPosition;
}

bool Arc3DAttributedPoint::operator!=(const Arc3DAttributedPoint& rhs)
{
	return !(*this == rhs);
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator-(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._constant = this->_constant;
	newPoint._position     = this->_position - rhs._position;
	newPoint._color        = this->_color    - rhs._color;
	newPoint._normalVector = this->_normalVector   - rhs._normalVector;

	newPoint._opacity = this->_opacity - rhs._opacity;
	newPoint._s       = this->_s       - rhs._s;
	newPoint._t       = this->_t       - rhs._t;
	newPoint._weight  = this->_weight  - rhs._weight;
	newPoint._worldPosition = this->_worldPosition - rhs._worldPosition;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator/(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._constant = this->_constant;
	newPoint._position = this->_position / rhs._position;
	newPoint._color    = this->_color    / rhs._color;
	newPoint._normalVector   = this->_normalVector   / rhs._normalVector;

	newPoint._opacity = this->_opacity / rhs._opacity;
	newPoint._s       = this->_s       / rhs._s;
	newPoint._t       = this->_t       / rhs._t;
	newPoint._weight  = this->_weight  / rhs._weight;
	newPoint._worldPosition = this->_worldPosition / rhs._worldPosition;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator*(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._constant = this->_constant;
	newPoint._position = this->_position * rhs._position;
	newPoint._color    = this->_color    * rhs._color;
	newPoint._normalVector   = this->_normalVector   * rhs._normalVector;

	newPoint._opacity = this->_opacity * rhs._opacity;
	newPoint._s       = this->_s       * rhs._s;
	newPoint._t       = this->_t       * rhs._t;
	newPoint._weight  = this->_weight  * rhs._weight;
	newPoint._worldPosition = this->_worldPosition * rhs._worldPosition;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator+(const Arc3DAttributedPoint& rhs) const
{
	Arc3DAttributedPoint newPoint;

	newPoint._constant = this->_constant;
	newPoint._position = this->_position + rhs._position;
	newPoint._color    = this->_color    + rhs._color;
	newPoint._normalVector   = this->_normalVector   + rhs._normalVector;

	newPoint._opacity = this->_opacity + rhs._opacity;
	newPoint._s       = this->_s       + rhs._s;
	newPoint._t       = this->_t       + rhs._t;
	newPoint._weight  = this->_weight  + rhs._weight;
	newPoint._worldPosition = this->_worldPosition + rhs._worldPosition;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator/(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._constant = this->_constant;
	newPoint._position = this->_position / rhs;
	newPoint._color    = this->_color    / rhs;
	newPoint._normalVector   = this->_normalVector   / rhs;

	newPoint._opacity = this->_opacity / rhs;
	newPoint._s       = this->_s       / rhs;
	newPoint._t       = this->_t       / rhs;
	newPoint._weight  = this->_weight  / rhs;
	newPoint._worldPosition = this->_worldPosition / rhs;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator*(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._constant = this->_constant;
	newPoint._position = this->_position * rhs;
	newPoint._color    = this->_color    * rhs;
	newPoint._normalVector   = this->_normalVector   * rhs;

	newPoint._opacity = this->_opacity * rhs;
	newPoint._s       = this->_s       * rhs;
	newPoint._t       = this->_t       * rhs;
	newPoint._weight  = this->_weight  * rhs;
	newPoint._worldPosition = this->_worldPosition * rhs;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator-(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._constant = this->_constant;
	newPoint._position = this->_position - rhs;
	newPoint._color    = this->_color    - rhs;
	newPoint._normalVector   = this->_normalVector   - rhs;

	newPoint._opacity = this->_opacity - rhs;
	newPoint._s       = this->_s       - rhs;
	newPoint._t       = this->_t       - rhs;
	newPoint._weight  = this->_weight  - rhs;
	newPoint._worldPosition = this->_worldPosition - rhs;

	return newPoint;
}

Arc3DAttributedPoint Arc3DAttributedPoint::operator+(const double rhs) const
{
	Arc3DAttributedPoint newPoint;

	if (rhs == 0.0)
	{
		return newPoint;
	}

	newPoint._constant = this->_constant;
	newPoint._position = this->_position + rhs;
	newPoint._color    = this->_color    + rhs;
	newPoint._normalVector   = this->_normalVector   + rhs;

	newPoint._opacity = this->_opacity + rhs;
	newPoint._s       = this->_s       + rhs;
	newPoint._t       = this->_t       + rhs;
	newPoint._weight  = this->_weight  + rhs;
	newPoint._worldPosition = this->_worldPosition + rhs;

	return newPoint;
}


// Public Methods - Static //

Arc3DAttributedPoint Arc3DAttributedPoint::interpolateTo(const Arc3DAttributedPoint& startPoint, const Arc3DAttributedPoint& endPoint, const double alpha)
{
	Arc3DAttributedPoint newPoint;

	newPoint._constant = startPoint._constant + ((endPoint._constant - startPoint._constant) * alpha);
	newPoint._position      = Arc3DPointH::interpolateTo(startPoint._position,      endPoint._position,      alpha);
	newPoint._color         =    ArcColor::interpolateTo(startPoint._color,         endPoint._color,         alpha);
	newPoint._normalVector  =   ArcVector::interpolateTo(startPoint._normalVector,  endPoint._normalVector,  alpha);
	newPoint._worldPosition =  Arc3DPoint::interpolateTo(startPoint._worldPosition, endPoint._worldPosition, alpha);

	newPoint._opacity = startPoint._opacity + ((endPoint._opacity - startPoint._opacity) * alpha);
	newPoint._s       = startPoint._s       + ((endPoint._s       - startPoint._s)       * alpha);
	newPoint._t       = startPoint._t       + ((endPoint._t       - startPoint._t)       * alpha);
	newPoint._weight  = startPoint._weight  + ((endPoint._weight  - startPoint._weight)  * alpha);

	return newPoint;
}


// Public Methods //

void Arc3DAttributedPoint::selfInterpolateTo(const Arc3DAttributedPoint& point, const double alpha)
{
	this->_constant += ((point._constant - this->_constant) * alpha);
	this->_position.    selfInterpolateTo(point._position,     alpha);
	this->_color.       selfInterpolateTo(point._color,        alpha);
	this->_normalVector.selfInterpolateTo(point._normalVector, alpha);
	this->_worldPosition.selfInterpolateTo(point._worldPosition, alpha);

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

void Arc3DAttributedPoint::updateWorldPosition(const Arc3DPoint& point)
{
	_worldPosition = point;
}

void Arc3DAttributedPoint::updateWorldPosition(const Arc3DPointH& point)
{
	// Does this need to be put to cartesian?
	_worldPosition.x(point.x());
	_worldPosition.y(point.y());
	_worldPosition.z(point.z());
}
