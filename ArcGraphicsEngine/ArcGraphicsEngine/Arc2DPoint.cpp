#include "Arc2DPoint.h"


// Constructor/Destructor(s) //

Arc2DPoint::Arc2DPoint()
	: _x (0)
	, _y (0)
{

}

Arc2DPoint::Arc2DPoint(int x, int y)
	: _x(x)
	, _y(y)
{
}

Arc2DPoint::~Arc2DPoint()
{
}


// Public Properties //

void      Arc2DPoint::x(const int value) { _y = value; }
const int Arc2DPoint::x() const          { return _x;  }

void      Arc2DPoint::y(const int value) { _y = value; }
const int Arc2DPoint::y() const          { return _y;  }

