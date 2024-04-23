#pragma once

#ifndef ARCEDGE_H
#define ARCEDGE_H

#include "Arc3DAttributedPoint.h"

struct ArcEdge
{
	int                  yLast; // Final scan line of edge
	Arc3DAttributedPoint p;     // The values of the edge on this scan line
	Arc3DAttributedPoint inc;   // The incremental changes for the values from scanline to scanline

	ArcEdge* next; // A pointer to link the edges together in edge tables.
};
#endif // !ARCEDGE_H