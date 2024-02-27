#pragma once

#ifndef ARCCOLOR_H
#define ARCCOLOR_H

// Stdlib
#include <stdint.h>


class ArcColor
{
public: // Constructor/Destructor(s) //

	ArcColor();
	ArcColor(const unsigned int color);
	ArcColor(const float red, const float green, const float blue);

	~ArcColor();


public: // Overload(s) //

	bool operator ==(ArcColor color);


public: // Properties //

	void               color(const unsigned int value);
	const unsigned int color() const;


public: // Static Properties //

	static unsigned int getGreenComponent(const unsigned int value);

	static unsigned int getBlueComponent(const unsigned int value);

	static unsigned int getRedComponent(const unsigned int value);


private: // Methods //

	const int colorFromFloat(const float red, const float green, const float blue);


public: // Static Variables //

	static const unsigned int BLUE    = 0x000000FF;
	static const unsigned int CYAN    = 0x0000FFFF;
	static const unsigned int GREEN   = 0x0000FF00;
	static const unsigned int MAGENTA = 0x00FF00FF;
	static const unsigned int BLACK   = 0x00000000;
	static const unsigned int RED     = 0x00FF0000;
	static const unsigned int WHITE   = 0x00FFFFFF;
	static const unsigned int YELLOW  = 0x00FFFF00;
	static const unsigned int NOCOLOR = 0xFF000000;


private: // Variables //

	unsigned int _color;
};

#endif // !ARCCOLOR_H