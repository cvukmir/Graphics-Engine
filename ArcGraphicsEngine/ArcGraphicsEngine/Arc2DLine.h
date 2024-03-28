#pragma once

#ifndef ARC2DLINE_H
#define ARC2DLINE_H

#include "Arc2DPoint.h"

class Arc2DLine
{
public: // Constructor/Destructor(s) //

	Arc2DLine();

	~Arc2DLine();


private: // Variables //

	Arc2DPoint _endPoint;
	Arc2DPoint _startPoint;
};

#endif // !ARC2DLINE_H
