#include "ArcVector.h"

#include <math.h>


ArcVector::ArcVector()
	: _x(0.0)
	, _y(0.0)
	, _z(0.0)
{
}

ArcVector::ArcVector(double x, double y, double z)
	: _x(x)
	, _y(y)
	, _z(z)
{
}

ArcVector::ArcVector(const Arc3DPoint& startPoint, const Arc3DPoint& endPoint)
	: _x(endPoint.x() - startPoint.x())
	, _y(endPoint.y() - startPoint.y())
	, _z(endPoint.z() - startPoint.z())
{
}

ArcVector::ArcVector(const Arc3DPointH& startPoint, const Arc3DPointH& endPoint)
{
	Arc3DPoint point1 = startPoint.toCartesianPoint();
	Arc3DPoint point2 =   endPoint.toCartesianPoint();

	_x = (point1.x() - point2.x());
	_y = (point1.y() - point2.y());
	_z = (point1.z() - point2.z());
}

ArcVector::~ArcVector()
{
}




// Public Properties //

void         ArcVector::x(const double value) { _y = value; }
const double ArcVector::x() const             { return _x;  }

void         ArcVector::y(const double value) { _y = value; }
const double ArcVector::y() const             { return _y;  }

void         ArcVector::z(const double value) { _z = value; }
const double ArcVector::z() const             { return _z;  }




// Public Methods - Overload //

void ArcVector::operator=(const ArcVector& point)
{
	this->_x = point._x;
	this->_y = point._y;
	this->_z = point._z;
}

bool ArcVector::operator==(const ArcVector& point)
{
	return this->_x == point._x &&
		   this->_y == point._y &&
		   this->_z == point._z;
}

bool ArcVector::operator!=(const ArcVector& point)
{
	return !(*this == point);
}

void ArcVector::operator+(const ArcVector& point)
{
	this->_x += point._x;
	this->_y += point._y;
	this->_z += point._z;
}

void ArcVector::operator-(const ArcVector& point)
{
	this->_x -= point._x;
	this->_y -= point._y;
	this->_z -= point._z;
}

void ArcVector::operator/(const ArcVector& point)
{
	this->_x = point._x != 0.0 ? this->_x / point._x : 0.0;
	this->_y = point._y != 0.0 ? this->_x / point._y : 0.0;
	this->_z = point._z != 0.0 ? this->_x / point._z : 0.0;
}

void ArcVector::operator*(const ArcVector& point)
{
	this->_x *= point._x;
	this->_y *= point._y;
	this->_z *= point._z;
}




// Public Methods //

ArcVector ArcVector::crossProduct(const ArcVector& point)
{
	return ArcVector(  (this->_y * point._z) - (this->_z * point._y),  // x
		             -((this->_x * point._z) - (this->_z * point._x)), // y
		               (this->_x * point._y) - (this->_y * point._x)); // z
}

double ArcVector::dot(const ArcVector& point)
{
	return (this->_x * point._x) + (this->_y * point._y) + (this->_z * point._z);
}

double ArcVector::magnitudeSquared()
{
	return (this->_x * this->_x) + (this->_y * this->_y) + (this->_z * this->_z);
}

void ArcVector::normalize()
{
	const double magnitude = ::sqrt(magnitudeSquared());

	_x = magnitude != 0.0 ? _x / magnitude : 0.0;
	_y = magnitude != 0.0 ? _y / magnitude : 0.0;
	_z = magnitude != 0.0 ? _z / magnitude : 0.0;

	return;
}
