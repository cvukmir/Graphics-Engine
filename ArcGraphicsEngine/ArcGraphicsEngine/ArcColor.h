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
	ArcColor(const float red, const float green, const float blue);

	~ArcColor();


public: // Overload(s) //

	/* Copy operator. */
	void operator=(const ArcColor& rhs) const;

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

	void       color(const uint value);
	const uint color() const;


public: // Static Properties //

	static uint getBlueComponent(const uint value);

	static uint getGreenComponent(const uint value);

	static uint getRedComponent(const uint value);


public: // Methods - Static //

	static uint colorFromFloat(const float red, const float green, const float blue);

	/* Interpolates a position between the two points using the given percentage. */
	static ArcColor interpolateTo(const ArcColor& startColor, const ArcColor& endColor, const double alpha);


public: // Methods //

	/* Interpolates this point a percentage distance to the given next point. */
	void selfInterpolateTo(const ArcColor& color, const double alpha);


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

	uint _color;
};

#endif // !ARCCOLOR_H