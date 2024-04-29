#pragma once

#ifndef ARC3DPOINT_H
#define ARC3DPOINT_H


class Arc3DPoint
{
public: // Constructor/Destructor(s) //

	Arc3DPoint();
	Arc3DPoint(double x, double y, double z);

	~Arc3DPoint();


public: // Properties //

	void         x(const double value); // Sets the x value of this point.
	const double x() const;             // Gets the x value of this point.

	void         y(const double value); // Sets the y value of this point.
	const double y() const;             // Gets the y value of this point.

	void         z(const double value); // Sets the z value of this point.
	const double z() const;             // Gets the z value of this point.


public: // Methods - Overload //

	/* Copy operator. */
	void operator=(const Arc3DPoint& point);

	/* Equality operator. */
	bool operator==(const Arc3DPoint& point);

	/* Inequality operator. */
	bool operator!=(const Arc3DPoint& point);

	/* Addition operator for two points. */
	Arc3DPoint operator+(const Arc3DPoint& point) const;

	/* Subtraction operator for two points. */
	Arc3DPoint operator-(const Arc3DPoint& point) const;

	/* Division operator for two points. */
	Arc3DPoint operator/(const Arc3DPoint& point) const;

	/* Multiplication operator for two points. */
	Arc3DPoint operator*(const Arc3DPoint& point) const;

	/* Multiplication operator for two points. */
	Arc3DPoint operator/(const double rhs) const;

	/* Multiplication operator for two points. */
	Arc3DPoint operator*(const double rhs) const;

	/* Multiplication operator for two points. */
	Arc3DPoint operator+(const double rhs) const;

	/* Multiplication operator for two points. */
	Arc3DPoint operator-(const double rhs) const;

	/* Scales this object by the given value. */
	void operator*(const double scalar);


public: // Methods - Static //

	/* Interpolates a position between the two points using the given percentage. */
	static Arc3DPoint interpolateTo(const Arc3DPoint& startPoint, const Arc3DPoint& endPoint, const double alpha);


public: // Methods - Override //

	/* Multiplies each coordinate by the scalar value. */
	virtual void scale(const double scalar);

	/* Interpolates this point a percentage distance to the given next point. */
	void selfInterpolateTo(const Arc3DPoint& point, const double alpha);


protected: // Variables //

	double _x; // This points' x coordinate.
	double _y; // This points' y coordinate.
	double _z; // This points' z coordinate.
};

#endif // !ARC3DPOINT_H