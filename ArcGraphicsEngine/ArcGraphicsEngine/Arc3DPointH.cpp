#include "Arc3DPointH.h"



// Constructor/Destructor(s) //

Arc3DPointH::Arc3DPointH()
	: _w(1.0)
	, _x(0.0)
	, _y(0.0)
	, _z(0.0)
{
}

Arc3DPointH::Arc3DPointH(double x, double y, double z)
	: _w(1.0)
	, _x(x)
	, _y(y)
	, _z(z)
{

}

Arc3DPointH::Arc3DPointH(double x, double y, double z, double w)
	: _w(w)
	, _x(x)
	, _y(y)
	, _z(z)
{
}

Arc3DPointH::Arc3DPointH(const Arc3DPoint& point)
	: _w(1.0)
	, _x(point.x())
	, _y(point.y())
	, _z(point.z())
{
}

Arc3DPointH::~Arc3DPointH()
{
}


// Public Properties //

const double Arc3DPointH::w() const             { return _w; }

void         Arc3DPointH::x(const double value) { _y = value; }
const double Arc3DPointH::x() const             { return _x;  }

void         Arc3DPointH::y(const double value) { _y = value; }
const double Arc3DPointH::y() const             { return _y;  }

void         Arc3DPointH::z(const double value) { _z = value; }
const double Arc3DPointH::z() const             { return _z;  }




// Public Methods - Overload //

void Arc3DPointH::operator=(const Arc3DPointH& point)
{
	this->_w = point._w;
	this->_x = point._x;
	this->_y = point._y;
	this->_z = point._z;
}

bool Arc3DPointH::operator==(const Arc3DPointH& point)
{
	return this->_w == point._w  &&
		   this->_x == point._x &&
		   this->_y == point._y &&
		   this->_z == point._z;
}

bool Arc3DPointH::operator!=(const Arc3DPointH& point)
{
	return !(*this == point);
}

Arc3DPointH Arc3DPointH::operator+(const Arc3DPointH& point) const
{
	return Arc3DPointH(this->_x + point._x,
		               this->_y + point._y,
		               this->_z + point._z,
		               this->_z + point._z);
}

Arc3DPointH Arc3DPointH::operator-(const Arc3DPointH& point) const
{
	return Arc3DPointH(this->_x - point._x,
		               this->_y - point._y,
		               this->_z - point._z,
		               this->_z - point._z);
}

Arc3DPointH Arc3DPointH::operator/(const Arc3DPointH& point) const
{
	return Arc3DPointH(point._w != 0.0 ? this->_w / point._w : 0.0,
		               point._x != 0.0 ? this->_x / point._x : 0.0,
		               point._y != 0.0 ? this->_x / point._y : 0.0,
		               point._z != 0.0 ? this->_x / point._z : 0.0);
}

Arc3DPointH Arc3DPointH::operator*(const Arc3DPointH& point) const
{
	return Arc3DPointH(this->_x * point._x,
		               this->_y * point._y,
		               this->_z * point._z,
		               this->_z * point._z);
}

void Arc3DPointH::operator*(const double scalar)
{
	scale(scalar);
}


// Public Methods //

void Arc3DPointH::scale(const double scalar)
{
	_w *= scalar;
	_x *= scalar;
	_y *= scalar;
	_z *= scalar;
}

Arc3DPoint Arc3DPointH::toCartesianPoint() const
{
	return _w == 0.0 ?
		Arc3DPoint(  0.0,     0.0,     0.0) :
		Arc3DPoint(_x / _w, _y / _w, _z / _w);
}
