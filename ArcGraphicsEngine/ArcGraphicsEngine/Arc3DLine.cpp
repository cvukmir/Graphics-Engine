#include "Arc3DLine.h"


Arc3DLine::Arc3DLine()
{
}

Arc3DLine::Arc3DLine(const Arc3DPoint& startPoint, const Arc3DPoint& endPoint)
{
	_startPoint = startPoint;
	_endPoint   = endPoint;
}

Arc3DLine::~Arc3DLine()
{
}

void              Arc3DLine::endPoint(const Arc3DPoint& value) { _endPoint = value; }
const Arc3DPoint& Arc3DLine::endPoint() const                  { return _endPoint;  }

void              Arc3DLine::startPoint(const Arc3DPoint& value) { _startPoint = value; }
const Arc3DPoint& Arc3DLine::startPoint() const                  { return _startPoint;  }