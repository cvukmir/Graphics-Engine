#include "Arc2DPoint.h"


// Constructor/Destructor(s) //

Arc2DPoint::Arc2DPoint()
	: _x (0.0)
	, _y (0.0)
{

}

Arc2DPoint::Arc2DPoint(double x, double y)
	: _x(x)
	, _y(y)
{
}

Arc2DPoint::~Arc2DPoint()
{
}


// Public Properties //

void         Arc2DPoint::x(const double value) { _y = value; }
const double Arc2DPoint::x() const             { return _x;  }

void         Arc2DPoint::y(const double value) { _y = value; }
const double Arc2DPoint::y() const             { return _y;  }