#pragma once

#ifndef ARC3DPOINTH_H
#define ARC3DPOINTH_H

#include "Arc3DPoint.h"

class Arc3DPointH
{
public: // Constructor/Destructor(s) //

	Arc3DPointH();
	Arc3DPointH(double x, double y, double z);
	Arc3DPointH(double x, double y, double z, double w);
	Arc3DPointH(const Arc3DPoint& point);

	~Arc3DPointH();


public: // Properties //

	const double w() const;             // Gets the w value of this point.

	void         x(const double value); // Sets the x value of this point.
	const double x() const;             // Gets the x value of this point.

	void         y(const double value); // Sets the y value of this point.
	const double y() const;             // Gets the y value of this point.

	void         z(const double value); // Sets the z value of this point.
	const double z() const;             // Gets the z value of this point.


public: // Methods - Overload //

	/* Copy operator. */
	void operator=(const Arc3DPointH& point);

	/* Equality operator. */
	bool operator==(const Arc3DPointH& point);

	/* Inequality operator. */
	bool operator!=(const Arc3DPointH& point);

	/* Addition operator for two points. */
	Arc3DPointH operator+(const Arc3DPointH& point) const;

	/* Subtraction operator for two points. */
	Arc3DPointH operator-(const Arc3DPointH& point) const;

	/* Division operator for two points. */
	Arc3DPointH operator/(const Arc3DPointH& point) const;

	/* Multiplication operator for two points. */
	Arc3DPointH operator*(const Arc3DPointH& point) const;

	/* Scales this object by the given value. */
	void operator*(const double scalar);


public: // Methods //

	/* Multiplies each coordinate by the scalar value. */
	void scale(const double scalar);

	/* Returns this object scaled to a cartesian point. */
	Arc3DPoint toCartesianPoint() const;


private: // Variables //

	double _w; // This point's w scale value.
	double _x; // This point's x coordinate.
	double _y; // This point's y coordinate.
	double _z; // This point's z coordinate.
};

#endif // !ARC3DPOINTH_H
