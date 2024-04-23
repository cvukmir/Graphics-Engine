#pragma once

#ifndef ARC3DATTRIBUTEDPOINT_H
#define ARC3DATTRIBUTEDPOINT_H

#include "ArcColor.h"
#include "ArcVector.h"
#include "Arc3DPointH.h"

class Arc3DAttributedPoint
{
public:

	Arc3DAttributedPoint();
	Arc3DAttributedPoint(const Arc3DPointH& point);
	Arc3DAttributedPoint(const Arc3DPoint& point);

	~Arc3DAttributedPoint();


public: // Properties //

	void              color(const ArcColor& value);
	const ArcColor&   color() const;

	void              opacity(const double value);
	const double      opacity() const;

	void              position(const Arc3DPointH& value);
	const Arc3DPointH position() const;

	void              textureS(const double value);
	const double      textureS() const;

	void              textureT(const double value);
	const double      textureT() const;

	void              vector(const ArcVector& value);
	const ArcVector&  vector() const;

	void              weight(const double value);
	const double      weight() const;


public: // Methods - Overload //

	/* Copy operator. */
	void operator=(const Arc3DAttributedPoint& rhs);

	/* Inequality operator. */
	bool operator==(const Arc3DAttributedPoint& rhs);

	/* Inequality operator. */
	bool operator!=(const Arc3DAttributedPoint& rhs);

	/* Subtraction operator for two attributed points. */
	Arc3DAttributedPoint operator-(const Arc3DAttributedPoint& rhs) const;

	/* Divison operator for two attributed points. */
	Arc3DAttributedPoint operator/(const Arc3DAttributedPoint& rhs) const;

	/* Subtraction operator for two attributed points. */
	Arc3DAttributedPoint operator*(const Arc3DAttributedPoint& rhs) const;

	/* Addition operator for two attributed points. */
	Arc3DAttributedPoint operator+(const Arc3DAttributedPoint& rhs) const;

	/* Divison operator for two attributed points. */
	Arc3DAttributedPoint operator/(const double rhs) const;

	/* Multiplication operator for two attributed points. */
	Arc3DAttributedPoint operator*(const double rhs) const;

	/* Subtraction operator for two attributed points. */
	Arc3DAttributedPoint operator-(const double rhs) const;

	/* Addition operator for two attributed points. */
	Arc3DAttributedPoint operator+(const double rhs) const;


public: // Methods - Static //

	/* Interpolates a position between the two points using the given percentage. */
	static Arc3DAttributedPoint interpolateTo(const Arc3DAttributedPoint& startPoint, const Arc3DAttributedPoint& endPoint, const double alpha);


public: // Methods

	/* Interpolates this point a percentage distance to the given next point. */
	void selfInterpolateTo(const Arc3DAttributedPoint& point, const double alpha);

	/* Updates the underlying position for this class to the given value. */
	void updatePosition(const Arc3DPoint& point);

	/* Updates the underlying position for this class to the given value. */
	void updatePosition(const Arc3DPointH& point);


private:

	ArcColor    _color;
	double      _opacity;
	Arc3DPointH _position;
	double      _s;
	double      _t;
	ArcVector   _vector;
	double      _weight;
};

#endif // !ARC3DATTRIBUTEDPOINT_H