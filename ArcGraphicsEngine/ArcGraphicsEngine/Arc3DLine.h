#pragma once

#ifndef ARC3DLINE_H
#define ARC3DLINE_H

#include "Arc3DPoint.h"

class Arc3DLine
{
public: // Constructor/Destructor(s) //

	Arc3DLine();
	Arc3DLine(const Arc3DPoint& startPoint, const Arc3DPoint& endPoint);

	~Arc3DLine();


public: // Properties //

	void              endPoint(const Arc3DPoint& value); // Sets the end point of this line.
	const Arc3DPoint& endPoint() const;                  // Gets the end point of this line.

	void              startPoint(const Arc3DPoint& value); // Sets the start point of this line.
	const Arc3DPoint& startPoint() const;                  // Gets the start point of this line.


private:

	Arc3DPoint _endPoint;
	Arc3DPoint _startPoint;
};

#endif // !ARC3DLINE_H