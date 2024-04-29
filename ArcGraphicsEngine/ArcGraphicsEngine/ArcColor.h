#pragma once

#ifndef ARCCOLOR_H
#define ARCCOLOR_H

// Stdlib
#include <stdint.h>

// ArcFramework
#include "ArcBaseTypes.h"

class ArcColor
{
public: // Constructor/Destructor(s) //

	ArcColor();
	ArcColor(const uint color);
	ArcColor(const double red, const double green, const double blue);

	~ArcColor();


public: // Overload(s) //

	/* Copy operator. */
	void operator=(const ArcColor& rhs);

	/* Equality operator. */
	bool operator==(const ArcColor& rhs) const;

	/* Subtraction operator for two colors. */
	ArcColor operator-(const ArcColor& rhs) const;

	/* Division operator for two colors. */
	ArcColor operator/(const ArcColor& rhs) const;

	/* Addition operator for two colors. */
	ArcColor operator+(const ArcColor& rhs) const;

	/* Multiplication operator for two colors. */
	ArcColor operator*(const ArcColor& rhs) const;

	/* Division operator for two colors. */
	ArcColor operator/(const double rhs) const;

	/* Multiplication operator for two colors. */
	ArcColor operator*(const double rhs) const;

	/* Subtraction operator for two colors. */
	ArcColor operator-(const double rhs) const;

	/* Addition operator for two colors. */
	ArcColor operator+(const double rhs) const;


public: // Properties //

	void         blue(const double value);
	const double blue() const;

	void         green(const double value);
	const double green() const;

	void         red(const double value);
	const double red() const;


public: // Static Properties //

	static uint getBlueComponent(const uint value);

	static uint getGreenComponent(const uint value);

	static uint getRedComponent(const uint value);


public: // Methods - Static //

	/* Interpolates a position between the two points using the given percentage. */
	static ArcColor interpolateTo(const ArcColor& startColor, const ArcColor& endColor, const double alpha);


public: // Methods //

	/* Interpolates this point a percentage distance to the given next point. */
	void selfInterpolateTo(const ArcColor& color, const double alpha);

	uint colorToUint() const;


private: // Methods //



public: // Static Variables //

	static const uint BLUE    = 0x000000FF;
	static const uint CYAN    = 0x0000FFFF;
	static const uint GREEN   = 0x0000FF00;
	static const uint MAGENTA = 0x00FF00FF;
	static const uint BLACK   = 0x00000000;
	static const uint RED     = 0x00FF0000;
	static const uint WHITE   = 0x00FFFFFF;
	static const uint YELLOW  = 0x00FFFF00;
	static const uint NOCOLOR = 0xFF000000;


private: // Variables //

	double _red;
	double _green;
	double _blue;
};

#endif // !ARCCOLOR_H