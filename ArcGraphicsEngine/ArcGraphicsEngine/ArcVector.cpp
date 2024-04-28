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

void ArcVector::operator=(const ArcVector& vector)
{
	this->_x = vector._x;
	this->_y = vector._y;
	this->_z = vector._z;
}

bool ArcVector::operator==(const ArcVector& vector)
{
	return this->_x == vector._x &&
		   this->_y == vector._y &&
		   this->_z == vector._z;
}

bool ArcVector::operator!=(const ArcVector& vector)
{
	return !(*this == vector);
}

ArcVector ArcVector::operator+(const ArcVector& vector) const
{
	return ArcVector(this->_x + vector._x,
		             this->_y + vector._y,
		             this->_z + vector._z);
}

ArcVector ArcVector::operator-(const ArcVector& vector) const
{
	return ArcVector(this->_x - vector._x,
		             this->_y - vector._y,
		             this->_z - vector._z);
}

ArcVector ArcVector::operator/(const ArcVector& vector) const
{
	return ArcVector(vector._x != 0.0 ? this->_x / vector._x : 0.0,
		             vector._y != 0.0 ? this->_x / vector._y : 0.0,
		             vector._z != 0.0 ? this->_x / vector._z : 0.0);
}

ArcVector ArcVector::operator*(const ArcVector& vector) const
{
	return ArcVector(this->_x * vector._x,
		             this->_y * vector._y,
		             this->_z * vector._z);
}

ArcVector ArcVector::operator/(const double rhs) const
{
	if (rhs == 0.0)
	{
		return ArcVector();
	}

	return ArcVector(this->_x / rhs,
		             this->_y / rhs,
		             this->_z / rhs);
}

ArcVector ArcVector::operator*(const double rhs) const
{
	return ArcVector(this->_x * rhs,
		             this->_y * rhs,
		             this->_z * rhs);
}

ArcVector ArcVector::operator-(const double rhs) const
{
	return ArcVector(this->_x - rhs,
		             this->_y - rhs,
		             this->_z - rhs);
}

ArcVector ArcVector::operator+(const double rhs) const
{
	return ArcVector(this->_x + rhs,
		             this->_y + rhs,
		             this->_z + rhs);
}


// Public Methods - Static //

ArcVector ArcVector::interpolateTo(const ArcVector& startVector, const ArcVector& endVector, const double alpha)
{
	return ArcVector(startVector.x() + (alpha * (endVector.x() - startVector.x())),
		             startVector.y() + (alpha * (endVector.y() - startVector.y())),
		             startVector.z() + (alpha * (endVector.z() - startVector.z())));
}


// Public Methods //

ArcVector ArcVector::crossProduct(const ArcVector& vector)
{
	return ArcVector(  (this->_y * vector._z) - (this->_z * vector._y),  // x
		             -((this->_x * vector._z) - (this->_z * vector._x)), // y
		               (this->_x * vector._y) - (this->_y * vector._x)); // z
}

double ArcVector::dot(const ArcVector& vector)
{
	return (this->_x * vector._x) + (this->_y * vector._y) + (this->_z * vector._z);
}

double ArcVector::magnitudeSquared() const
{
	return (this->_x * this->_x) + (this->_y * this->_y) + (this->_z * this->_z);
}

void ArcVector::normalize()
{
	const double magnitude = ::sqrt(magnitudeSquared());

	_x = magnitude != 0.0 ? _x / magnitude : 0.0;
	_y = magnitude != 0.0 ? _y / magnitude : 0.0;
	_z = magnitude != 0.0 ? _z / magnitude : 0.0;
}

void ArcVector::reflect(const ArcVector& reflectAbout)
{
	(*this) = (((reflectAbout * (*this)) * 2) / reflectAbout.magnitudeSquared()) * reflectAbout - (*this);
}

void ArcVector::selfInterpolateTo(const ArcVector& vector, const double alpha)
{
	_x = _x + (alpha * (vector.x() - _x));
	_y = _y + (alpha * (vector.y() - _y));
	_z = _z + (alpha * (vector.z() - _z));
}
