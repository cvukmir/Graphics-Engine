#pragma once

#ifndef ARCBASEOBJECT_H
#define ARCBASEOBJECT_H

#include <vector>

#include "ArcTypedefs.h"
#include "ArcEdge.hpp"

class ArcEdgeTable
{
public: // Constructor/Destructor(s) //

	ArcEdgeTable(const uint scanlineCount);

	~ArcEdgeTable();


public: // Methods //

	void scan_convert(Arc3DAttributedPointList& pointList);

	bool buildEdgeList(Arc3DAttributedPointList& pointList);

	void makeEdgeRec(Arc3DAttributedPoint* upper, Arc3DAttributedPoint* lower);

	void addActiveList(const uint scanLine, ArcEdge* pEdge);

	void insertEdge(ArcEdge* edgeList, ArcEdge* pEdge);

	void updateAET(const uint scanLine, ArcEdge* pEdge);

	void deleteAfter(ArcEdge* pEdge);

	void resortAET();

	void fillBetweenEdges(const uint scanLine);


private: // Methods //

	/* Clear the edges in the nested list of the edge table. */
	void clearEdgeTable();


private: 

	ArcEdge*              _activeEdgeTable;
	std::vector<ArcEdge*> _edgeTable;
};


#endif // !ARCBASEOBJECT_H