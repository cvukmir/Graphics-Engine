#pragma once

#ifndef ARCVECTOR_H
#define ARCVECTOR_H

#include "Arc3DPoint.h"
#include "Arc3DPointH.h"

class ArcVector
{
public: // Constructor/Destructor(s) //

	ArcVector();
	ArcVector(double x, double y, double z);
	ArcVector(const Arc3DPoint& startPoint, const Arc3DPoint& endPoint);
	ArcVector(const Arc3DPointH& startPoint, const Arc3DPointH& endPoint);

	~ArcVector();


public: // Properties //

	void         x(const double value); // Sets the x value of this vector.
	const double x() const;             // Gets the x value of this vector.

	void         y(const double value); // Sets the y value of this vector.
	const double y() const;             // Gets the y value of this vector.

	void         z(const double value); // Sets the z value of this vector.
	const double z() const;             // Gets the z value of this vector.


public: // Methods - Overload //

	/* Copy operator. */
	void operator=(const ArcVector& vector);

	/* Equality operator. */
	bool operator==(const ArcVector& vector);

	/* Inequality operator. */
	bool operator!=(const ArcVector& vector);

	/* Addition operator for two vectors. */
	ArcVector operator+(const ArcVector& vector) const;

	/* Subtraction operator for two vectors. */
	ArcVector operator-(const ArcVector& vector) const;

	/* Division operator for two vectors. */
	ArcVector operator/(const ArcVector& vector) const;

	/* Multiplication operator for two vectors. */
	ArcVector operator*(const ArcVector& vector) const;

	/* Division operator for two vectors. */
	ArcVector operator/(const double rhs) const;

	/* Multiplication operator for two vectors. */
	ArcVector operator*(const double rhs) const;

	/* Subtraction operator for two vectors. */
	ArcVector operator-(const double rhs) const;

	/* Addition operator for two vectors. */
	ArcVector operator+(const double rhs) const;


public: // Methods - Static //

	/* Interpolates a position between the two vectors using the given percentage. */
	static ArcVector interpolateTo(const ArcVector& startvector, const ArcVector& endvector, const double alpha);


public: // Methods //

	/* Computes the cross product and returns the vector value. */
	ArcVector crossProduct(const ArcVector& vector);

	/* Computes the dot product and returns the scalar value. */
	double dot(const ArcVector& vector);

	/* Computes the squared magnitued of this vector. */
	double magnitudeSquared() const;

	/* Normalizes this vector inplace. */
	void normalize();

	void reflect(const ArcVector& reflectAbout);

	/* Interpolates this vector a percentage distance to the given next vector. */
	void selfInterpolateTo(const ArcVector& vector, const double alpha);


private: // Variables
	
	double _x;
	double _y;
	double _z;
};

#endif // !ARCVECTOR_H
