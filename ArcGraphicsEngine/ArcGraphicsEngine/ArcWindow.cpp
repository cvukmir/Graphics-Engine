#include "ArcWindow.h"
#include "ArcColor.h"

ArcWindow::ArcWindow()
	: _height (0)
	, _pMemory(nullptr)
	, _width  (0) 
{
}

ArcWindow::~ArcWindow()
{
	delete _pMemory;
}

ArcWindow* ArcWindow::window()
{
	if (!_pInstancePtr)
	{
		_pInstancePtr = new ArcWindow();
	}

	return _pInstancePtr;
}

void ArcWindow::drawPixel(const int xPos, const int yPos, const ArcColor color)
{
	if (!inWindow(xPos, yPos))
	{
		return;
	}

	*(_pMemory + (_width * yPos) + xPos) = color.color();
}

void          ArcWindow::memory(UINT32* value)     { _pMemory = value; }
const UINT32* ArcWindow::memory()            const { return _pMemory; }

void      ArcWindow::windowHeight(const int value) { _height = value; }
const int ArcWindow::windowHeight()          const { return _height; }

void      ArcWindow::windowWidth(const int value) { _width = value; }
const int ArcWindow::windowWidth()          const { return _width; }

void ArcWindow::initializeMemory()
{
	int size = _width * _height;

	_pMemory = new UINT32[size];

	UINT32* pixel = _pMemory;
	for (int i = 0; i < size; ++i, ++pixel)
	{
		*pixel = ArcColor::WHITE;
	}
}


void ArcWindow::drawLine(const Arc2DPoint startPoint, const Arc2DPoint endPoint, ArcColor color)
{
	const int deltaX = endPoint.x() - startPoint.x();
	const int deltaY = endPoint.y() - startPoint.x();

	int x = startPoint.x();
	int y = startPoint.y();
	int p = (2 * deltaY) - deltaX;

	const int endX = endPoint.x();
	for (; x <= endX; ++x)
	{
		drawPixel(x, y, color);
		if (p > 0)
		{
			y++;
			p += (2 * deltaY) - (2 * deltaX);
		}
		else
		{
			p += 2 * deltaY;
		}
	}
}

void ArcWindow::drawCircle(const Arc2DPoint startPoint, const int radius, const ArcColor color)
{
	const int startPointX = startPoint.x();
	const int startPointY = startPoint.y();

	int x = 0;
	int y = radius;
	int p = 1 - radius;

	while (y >= x)
	{
		drawPixel(startPointX + x, startPointY + y, color);
		drawPixel(startPointY + y, startPointX + x, color);
		drawPixel(startPointY + y, startPointX - x, color);
		drawPixel(startPointX - x, startPointY + y, color);
		drawPixel(startPointX - x, startPointY - y, color);
		drawPixel(startPointY - y, startPointX - x, color);
		drawPixel(startPointY - y, startPointX + x, color);
		drawPixel(startPointX + x, startPointY - y, color);

		++x;
		if (p >= 0)
		{
			--y;
			p += (2 * x) + 1 - (2 * y);
		}
		else
		{
			p += (2 * x) + 1;
		}
	}
}

bool ArcWindow::findspan(int& startX, int& endX, const int y, const ArcColor seedcolor)
{
//	x = xs = xe
//	if (color(x,y) != seedcolor)
//		return false
//	// go right
//	While (xe < screenlength)
//		If (color(xe, y) != seedcolor)
//			Break;
//		Xe++
//	// go left
//	While(xe > 0)
//		If color(x, y) != seedcolor
//			Break
//		Xs = x
//		x—
//	return true
	int x = endX;
	startX = endX;
	return true;
}

void ArcWindow::fff4(const int startX, const int endX, const int y, ArcColor seedColor)
{
//	fillspan()
//		for (newxs = newxe = xs; newxe < xe; newxs = newxe)
//			if (findspan(newxs, newxe, y + 1…))
//				fff4(newxs, newxe, y + 1, …)
//			else
//				newxe++
//				// add same call but y-1 instead for checking down

}

bool ArcWindow::inWindow(const int xPos, const int yPos)
{
	if (xPos < 0 || xPos >= _width ||
		yPos < 0 || yPos >= _height)
	{
		return false;
	}

	return true;
}