#pragma once

#ifndef ARCCOLOR_H
#define ARCCOLOR_H

#include <stdint.h>

class ArcColor
{
public:

	ArcColor();
	ArcColor(unsigned int color);

	~ArcColor();

	void               color(const unsigned int value);
	const unsigned int color() const;

	static const unsigned int BLUE    = 0x000000FF;
	static const unsigned int CYAN    = 0x0000FFFF;
	static const unsigned int GREEN   = 0x0000FF00;
	static const unsigned int MAGENTA = 0x00FF00FF;
	static const unsigned int BLACK   = 0x00000000;
	static const unsigned int RED     = 0x00FF0000;
	static const unsigned int WHITE   = 0x00FFFFFF;
	static const unsigned int YELLOW  = 0x00FFFF00;


private:

	unsigned int _color;
};

#endif // !ARCCOLOR_H