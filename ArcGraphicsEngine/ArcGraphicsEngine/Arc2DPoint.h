#pragma once

#ifndef Arc2DPoint_H
#define Arc2DPoint_H

class Arc2DPoint
{
public: // Constructor/Destructor(s) //

	Arc2DPoint();
	Arc2DPoint(int x, int y);

	~Arc2DPoint();


public: // Methods //

	void      x(const int value); // Sets the x value of this point.
	const int x() const;          // Gets the x value of this point.

	void      y(const int value); // Sets the y value of this point.
	const int y() const;          // Gets the x value of this point.


private: // Variables //

	int _x;
	int _y;

};

#endif // !Arc2DPoint_H