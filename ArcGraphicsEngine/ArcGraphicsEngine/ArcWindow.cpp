#include "ArcWindow.h"
#include "ArcColor.h"

ArcWindow::ArcWindow()
	: _height      (256)
	, _pMemory     (nullptr)
	, _width       (256) 
	, _isRunning   (true)
	, _frameNumber (0)
	, _currentColor(ArcColor::WHITE)
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

void ArcWindow::drawPixel(const int xPos, const int yPos)
{
	if (!inWindow(xPos, yPos))
	{
		return;
	}

	*(_pMemory + (_width * yPos) + xPos) = _currentColor.color();
}

void           ArcWindow::memory(UINT32* value)     { _pMemory = value; }
const UINT32*  ArcWindow::memory()            const { return _pMemory; }

void           ArcWindow::windowHeight(const int value) { _height = value; }
const int      ArcWindow::windowHeight()          const { return _height; }

void           ArcWindow::windowWidth(const int value) { _width = value; }
const int      ArcWindow::windowWidth()          const { return _width; }

void           ArcWindow::isRunning(const bool value) { _isRunning = value; }
const bool     ArcWindow::isRunning() const           { return _isRunning; }

void           ArcWindow::frameNumber(const int value) { _frameNumber = value; }
const int      ArcWindow::frameNumber() const          { return _frameNumber; }

void           ArcWindow::currentColor(const ArcColor value) { _currentColor = value; }
const ArcColor ArcWindow::currentColor() const               { return _currentColor; }

void ArcWindow::initializeMemory()
{
	_pMemory = new UINT32[_width * _height];

	fillBackground(ArcColor::BLACK);
}

void ArcWindow::fillBackground(const ArcColor color)
{
	UINT32* pixel = _pMemory;
	for (int i = 0; i < _width * _height; ++i, ++pixel)
	{
		*pixel = color.color();
	}
}

void ArcWindow::drawPoint(const Arc2DPoint point)
{
	drawPixel(point.x(), point.y());
}

void ArcWindow::drawLine(const Arc2DPoint startPoint, const Arc2DPoint endPoint)
{
	const int deltaX = endPoint.x() - startPoint.x();
	const int deltaY = endPoint.y() - startPoint.y();

	const int twoDeltaX = 2 * abs(deltaX);
	const int twoDeltaY = 2 * abs(deltaY);

	if (deltaX == 0 && deltaY > 0)
	{
		for (int y = startPoint.y(); y <= endPoint.y(); ++y)
		{
			drawPixel(startPoint.x(), y);
		}
	}
	else if (deltaX == 0 && deltaY < 0)
	{
		for (int y = startPoint.y(); y >= endPoint.y(); --y)
		{
			drawPixel(startPoint.x(), y);
		}
	}
	else if (abs(deltaY) <= abs(deltaX))
	{
		int x = startPoint.x();
		int y = startPoint.y();
		int p = twoDeltaY - deltaX;
		const int endX = deltaX > 0 ? endPoint.x() : endPoint.x() + (2 * abs(deltaX));
		for (; x <= endX; ++x)
		{
			int xOffset = deltaX > 0 ? 0 : 2 * (x - startPoint.x());
			drawPixel(x - xOffset, y);
			if (p > 0)
			{
				deltaY > 0 ? ++y : --y;
				p += twoDeltaY - twoDeltaX;
			}
			else
			{
				p += twoDeltaY;
			}
		}
	}
	else if (abs(deltaY) > abs(deltaX))
	{
		int x = startPoint.x();
		int y = startPoint.y();
		int p = twoDeltaX - deltaY;
		const int endY = deltaY > 0 ? endPoint.y() : endPoint.y() + (2 * abs(deltaY));
		for (; y <= endY; ++y)
		{
			int yOffset = deltaY > 0 ? 0 : 2 * (y - startPoint.y());
			drawPixel(x, y - yOffset);
			if (p > 0)
			{
				deltaX > 0 ? ++x : --x;
				p += twoDeltaX - twoDeltaY;
			}
			else
			{
				p += twoDeltaX;
			}
		}
	}
}

void ArcWindow::drawCircle(const Arc2DPoint startPoint, const int radius)
{
	const int startPointX = startPoint.x();
	const int startPointY = startPoint.y();

	int x = 0;
	int y = radius;
	int p = 1 - radius;

	while (y >= x)
	{
		drawPixel(startPointX + x, startPointY + y);
		drawPixel(startPointX + y, startPointY + x);
		drawPixel(startPointX + y, startPointY - x);
		drawPixel(startPointX - x, startPointY + y);
		drawPixel(startPointX - x, startPointY - y);
		drawPixel(startPointX - y, startPointY - x);
		drawPixel(startPointX - y, startPointY + x);
		drawPixel(startPointX + x, startPointY - y);

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

void ArcWindow::fill(const Arc2DPoint startPoint)
{
	int newStartX = startPoint.x();
	int newEndX   = newStartX;
	ArcColor seedColor = colorAt(startPoint.x(), startPoint.y());
	findspan(newStartX, newEndX, startPoint.y(), seedColor);
	fff4(newStartX, newEndX, startPoint.y(), 1, seedColor);
	fff4(newStartX, newEndX, startPoint.y(), -1, seedColor);
}

ArcColor ArcWindow::colorAt(const int xPos, const int yPos)
{
	return ArcColor(*(_pMemory + (_width * yPos) + xPos));
}

void ArcWindow::fillSpan(const int startX, const int endX, const int y)
{
	for (int i = startX; i < endX; ++i)
	{
		drawPixel(i, y);
	}
}

bool ArcWindow::findspan(int& startX, int& endX, const int y, ArcColor seedColor)
{
	if (!inWindow(startX, y))
	{
		return false;
	}

	endX = startX;
	int x = startX;
	if (colorAt(x, y).color() != seedColor.color())
	{
		return false;
	}

	while (endX < _width)
	{
		// go right
		if (colorAt(endX, y).color() != seedColor.color())
		{
			break;
		}
		++endX;
	}
	// go left
	while(endX > 0)
	{
		if (colorAt(x, y).color() != seedColor.color())
		{
			break;
		}
		startX = x;
		--x;
	}
	return true;
}

void ArcWindow::fff4(const int startX, const int endX, const int y, const int offset, ArcColor seedColor)
{
	fillSpan(startX, endX, y);
	int holdX = startX;

	//findspan(xs, xe, y);
	int newxs = startX;
	int newxe = startX;
	for (; newxe < endX; newxs = newxe)
	{
		if (findspan(newxs, newxe, y + offset, seedColor))
		{
			fff4(newxs, newxe, y + offset, offset, seedColor);
		}
		else
		{
			newxe++;
		}
	}
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