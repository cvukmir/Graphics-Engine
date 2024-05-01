#include "ArcEdgeTable.h"
#include "ArcEdge.hpp"
#include "ArcWindow.h"
#include <vector>
#include <math.h>
#include "ArcColor.h"
#include "Arc3DAttributedPoint.h"

// Constructor/Destructor(s) //

ArcEdgeTable::ArcEdgeTable(const uint scanlineCount)
	: _activeEdgeTable(new ArcEdge())
	, _edgeTable      (scanlineCount)
{
}

ArcEdgeTable::~ArcEdgeTable()
{
	delete(_activeEdgeTable);
}


// Public Methods //

void ArcEdgeTable::scan_convert(Arc3DAttributedPointList& pointList)
{
	if (!buildEdgeList(pointList))
	{
		// No edges cross a scanline
		return;
	}

	clearEdgeTables();

	for (uint scan = 0U; scan < _edgeTable.size(); ++scan)
	{
		// Take the edges starting on this scanline from the edge table and add them to the active edge table(AET).
		if (_edgeTable[scan])
		{
			addActiveList(scan, _activeEdgeTable);
		}

		if (_activeEdgeTable->next)
		{
			// fill between the edge pairs in the AET
			fillBetweenEdges(scan);

			// update the AET
			updateAET(scan, _activeEdgeTable);
			
			// resort the AET
			resortAET();
		}
	}

	clearEdgeTables();
}

bool ArcEdgeTable::buildEdgeList(Arc3DAttributedPointList& pointList)
{
	bool scanlineCrossed = false;
	
	uint vertex1 = pointList.size() - 1U; // Initialize to the last vertex in the polygon
	
	for (uint vertex2 = 0U; vertex2 < pointList.size(); ++vertex2)
	{
		double v1y = ::ceil(pointList[vertex1]->position().y());
		double v2y = ::ceil(pointList[vertex2]->position().y());

		if (v1y != v2y)
		{
			scanlineCrossed = true;
	
			if (pointList[vertex1]->position().y() < pointList[vertex2]->position().y())
			{
				//Make an edge record from vertex[v1] to vertex[v2]
				makeEdgeRec(pointList[vertex2], pointList[vertex1]);
			}
			else
			{
				//Make an edge record from vertex[v2] to vertex[v1]
				makeEdgeRec(pointList[vertex1], pointList[vertex2]);
			}
		}
		vertex1 = vertex2; // Move to next edge
	}
	
	return scanlineCrossed;
}

void ArcEdgeTable::makeEdgeRec(Arc3DAttributedPoint* upper, Arc3DAttributedPoint* lower)
{
	double dy = upper->position().y() - lower->position().y();
	
	ArcEdge* pNewEdge = new ArcEdge();
	
	// Calculate the edge value increments between scan lines
	pNewEdge->inc = (*upper - *lower) / dy;
	
	// Edge starts on scanline ceil(lower.y)
	double factor = ceil(lower->position().y()) - lower->position().y(); // Gives the fractional position of the first scanline crossing
	
	// Calculate the starting values for the edge
	pNewEdge->p = *lower + (pNewEdge->inc * factor);
	
	// Find the last scanline for the edge
	pNewEdge->yLast = static_cast<int>(ceil(upper->position().y())) - 1;
	
	// Insert e into the edge table list of edges starting on scanline ceil(lower.y)
	if (ArcEdge* pExistingEdge = _edgeTable[ceil(lower->position().y())])
	{
		insertEdge(_edgeTable[ceil(lower->position().y())], pNewEdge);
	}
	else
	{
		_edgeTable[ceil(lower->position().y())] = pNewEdge;
	}
}

void ArcEdgeTable::addActiveList(const uint scanLine, ArcEdge* pEdge)
{
	ArcEdge* p = nullptr;
	ArcEdge* q = nullptr;

	p = _edgeTable[scanLine]; // Get the edges starting on this scan line
	
	while (p)
	{
		q = p->next; // Hold the rest of the list
		insertEdge(pEdge, p);
		p = q;
	}
	
	// Keep edge table clean -- edges have been transfered
	_edgeTable[scanLine] = nullptr;
}

void ArcEdgeTable::insertEdge(ArcEdge* edgeList, ArcEdge* pEdge)
{
	ArcEdge* p;
	ArcEdge* q = edgeList;

	// p leads
	p = q->next;

	while (p && (pEdge->p.position().x() > p->p.position().x()))
	{
		// Step to the next edge
		q = p;
		p = p->next;
	}

	// Link the edge into the list after q
	pEdge->next = q->next;
	q->next = pEdge;
}

void ArcEdgeTable::updateAET(const uint scanLine, ArcEdge* pEdge)
{
	ArcEdge* q = pEdge;
	ArcEdge* p = pEdge->next;
	// p leads
	
	while (p)
	{
		if (scanLine == p->yLast)  // This is the last scanline for this edge
		{
			p = p->next;    // Move p along
			deleteAfter(q); // get rid of old node
		}
		else
		{
			// Update the attribute values
			p->p = p->p + p->inc;
			q = p;
			p = p->next;
		}
	}
}

void ArcEdgeTable::deleteAfter(ArcEdge* pEdge)
{
	ArcEdge* p = pEdge->next;

	pEdge->next = p->next;
	delete p;
}

void ArcEdgeTable::resortAET()
{
	ArcEdge* q;
	ArcEdge* p = _activeEdgeTable->next;
	
	_activeEdgeTable->next = nullptr;
	while (p)
	{
		q = p->next;
		insertEdge(_activeEdgeTable, p);
		p = q;
	}
}

void ArcEdgeTable::fillBetweenEdges(const uint scanLine)
{
	ArcEdge* p1;
	ArcEdge* p2;

	p1 = _activeEdgeTable->next;
	while (p1)
	{
		p2 = p1->next;  // Get the pair of edges from the AET

		if (p1->p.position().x() != p2->p.position().x())
		{
			// Calculate the attribute increments along the scanline
			double dx = p2->p.position().x() - p1->p.position().x();
			Arc3DAttributedPoint inc = (p2->p - p1->p) / dx;

			// Calculate the starting values for the edge
			double factor = ceil(p1->p.position().x()) - p1->p.position().x(); // Gives the fractional position of the first pixel crossing

			Arc3DAttributedPoint value = p1->p + (inc * factor);

			double endx = ceil(p2->p.position().x());

			while (value.position().x() < endx)
			{
				_surfacePointValues = value;
				_surfacePointValues = _surfacePointValues / _surfacePointValues.constant();
				ArcWindow::window()->_pSurfaceShader(&_surfacePointValues);

				//Calculate the color for the pixel and plot it. x and z come from the current values, y is the current scanline
				//ArcWindow::window()->draw3DPixel(Arc3DPoint(value.position().x(), scanLine, value.position().z()), value.color());
				ArcWindow::window()->draw3DPixel(Arc3DPoint(_surfacePointValues.position().x(), _surfacePointValues.position().y(), _surfacePointValues.position().z()), _surfacePointValues.color());

				// Increment the values
				value = value + inc;
			}
		}
		p1 = p2->next;
	}
}


// Private Methods //

void ArcEdgeTable::clearEdgeTables()
{
	ArcEdge* pCurrentNode = _activeEdgeTable->next;

	if (!pCurrentNode)
	{
		// Already clear!
		return;
	}

	while (ArcEdge* pNextNode = pCurrentNode->next)
	{
		delete (pCurrentNode);
		pCurrentNode = pNextNode;
	}

	delete(pCurrentNode);

	_activeEdgeTable->next = nullptr;
}

