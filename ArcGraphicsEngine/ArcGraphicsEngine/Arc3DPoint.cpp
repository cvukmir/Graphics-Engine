#include "Arc3DPoint.h"

#include "Arc3DPointH.h"


// Constructor/Destructor(s) //

Arc3DPoint::Arc3DPoint()
	: _x(0.0)
	, _y(0.0)
	, _z(0.0)
{

}

Arc3DPoint::Arc3DPoint(double x, double y, double z)
	: _x(x)
	, _y(y)
	, _z(z)
{
}

Arc3DPoint::~Arc3DPoint()
{
}




// Public Properties //

void         Arc3DPoint::x(const double value) { _y = value; }
const double Arc3DPoint::x() const             { return _x;  }

void         Arc3DPoint::y(const double value) { _y = value; }
const double Arc3DPoint::y() const             { return _y;  }

void         Arc3DPoint::z(const double value) { _z = value; }
const double Arc3DPoint::z() const             { return _z;  }




// Public Methods - Overload //

void Arc3DPoint::operator=(const Arc3DPoint& point)
{
	this->_x = point._x;
	this->_y = point._y;
	this->_z = point._z;
}

bool Arc3DPoint::operator==(const Arc3DPoint& point)
{
	return this->_x == point._x &&
		   this->_y == point._y &&
		   this->_z == point._z;
}

bool Arc3DPoint::operator!=(const Arc3DPoint& point)
{
	return !(*this == point);
}

Arc3DPoint Arc3DPoint::operator+(const Arc3DPoint& point) const
{
	return Arc3DPoint(this->_x + point._x,
		              this->_y + point._y,
		              this->_z + point._z);
}

Arc3DPoint Arc3DPoint::operator-(const Arc3DPoint& point) const
{
	return Arc3DPoint(this->_x - point._x,
		              this->_y - point._y,
		              this->_z - point._z);
}

Arc3DPoint Arc3DPoint::operator/(const Arc3DPoint& point) const
{
	return Arc3DPoint(point._x != 0.0 ? this->_x / point._x : 0.0,
		              point._y != 0.0 ? this->_x / point._y : 0.0,
		              point._z != 0.0 ? this->_x / point._z : 0.0);
}

Arc3DPoint Arc3DPoint::operator*(const Arc3DPoint& point) const
{
	return Arc3DPoint(this->_x * point._x,
		              this->_y * point._y,
		              this->_z * point._z);
}

void Arc3DPoint::operator*(const double scalar)
{
	scale(scalar);
}




// Public Methods - Override //

void Arc3DPoint::scale(const double scalar)
{
	_x *= scalar;
	_y *= scalar;
	_z *= scalar;
}
