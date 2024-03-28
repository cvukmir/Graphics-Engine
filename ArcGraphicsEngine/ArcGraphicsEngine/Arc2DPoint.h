#pragma once

#ifndef ARC2DPOINT_H
#define ARC2DPOINT_H

class Arc2DPoint
{
public: // Constructor/Destructor(s) //

	Arc2DPoint();
	Arc2DPoint(double x, double y);

	~Arc2DPoint();


public: // Properties //

	void         x(const double value); // Sets the x value of this point.
	const double x() const;             // Gets the x value of this point.

	void         y(const double value); // Sets the y value of this point.
	const double y() const;             // Gets the y value of this point.


private: // Variables //

	double _x;
	double _y;

};

#endif // !ARC2DPOINT_H