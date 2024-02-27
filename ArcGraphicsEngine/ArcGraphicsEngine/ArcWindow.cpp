// ArcMain
#include "ArcWindow.h"
#include "ArcColor.h"


// Private Constructor //

ArcWindow::ArcWindow()
	: _currentColor(ArcColor::WHITE)
	, _frameNumber (0)
	, _height      (256)
	, _isRunning   (true)
	, _pMemory     (nullptr)
	, _width       (256)
{
}


// Public Destructor //

ArcWindow::~ArcWindow()
{
	delete _pMemory;
}


// Public Static Methods (Singleton) //

ArcWindow* ArcWindow::window()
{
	if (!_pInstancePtr)
	{
		_pInstancePtr = new ArcWindow();
	}

	return _pInstancePtr;
}


// Public Properties //

const UINT32*  ArcWindow::memory() const                     { return _pMemory; }

void           ArcWindow::windowHeight(const int value)      { _height = value; }
const int      ArcWindow::windowHeight() const               { return _height;  }

void           ArcWindow::windowWidth(const int value)       { _width = value; }
const int      ArcWindow::windowWidth() const                { return _width;  }

void           ArcWindow::isRunning(const bool value)        { _isRunning = value; }
const bool     ArcWindow::isRunning() const                  { return _isRunning;  }

void           ArcWindow::frameNumber(const int value)       { _frameNumber = value; }
const int      ArcWindow::frameNumber() const                { return _frameNumber;  }

void           ArcWindow::currentColor(const ArcColor value) { _currentColor = value; }
const ArcColor ArcWindow::currentColor() const               { return _currentColor;  }


// Public Methods //

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

void ArcWindow::drawLine(const Arc2DPoint startPoint, const Arc2DPoint endPoint)
{
	const int deltaX = endPoint.x() - startPoint.x();
	const int deltaY = endPoint.y() - startPoint.y();

	const int twoDeltaX = 2 * abs(deltaX);
	const int twoDeltaY = 2 * abs(deltaY);

	int x = startPoint.x();
	int y = startPoint.y();

	if (deltaX == 0 && deltaY > 0)
	{
		// Vertical line that increases in y.
		for (int y = startPoint.y(); y <= endPoint.y(); ++y)
		{
			drawPixel(startPoint.x(), y);
		}
	}
	else if (deltaX == 0 && deltaY < 0)
	{
		// Vertical line that decreases in y.
		for (int y = startPoint.y(); y >= endPoint.y(); --y)
		{
			drawPixel(startPoint.x(), y);
		}
	}
	else if (abs(deltaY) <= abs(deltaX))
	{
		// Line no greater that 45 degrees from x-axis in any direction.
		int       p    = twoDeltaY - abs(deltaX);
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
		// Line greater than 45 degrees from x-axis in any direction.
		int       p    = twoDeltaX - abs(deltaY);
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

void ArcWindow::drawPoint(const Arc2DPoint point)
{
	drawPixel(point.x(), point.y());
}

void ArcWindow::fill(const Arc2DPoint startPoint)
{
	int            newStartX = startPoint.x();
	int            newEndX   = newStartX;
	const ArcColor seedColor = colorAt(startPoint.x(), startPoint.y());

	// Find the span for this first y position.
	findspan(newStartX, newEndX, startPoint.y(), seedColor);

	// Find any spans above this first position.
	fastFloodFill(newStartX, newEndX, startPoint.y(), seedColor);

	// Find any spans below this first position.
	fastFloodFill(newStartX, newEndX, startPoint.y(), seedColor);
}

void ArcWindow::fillBackground(const ArcColor color)
{
	UINT32* pixel = _pMemory;
	for (int i = 0; i < _width * _height; ++i, ++pixel)
	{
		*pixel = color.color();
	}
}

void ArcWindow::initializeMemory()
{
	_pMemory = new UINT32[_width * _height];

	fillBackground(ArcColor::BLACK);
}


// Private Methods //

ArcColor ArcWindow::colorAt(const int xPos, const int yPos)
{
	return ArcColor(*(_pMemory + (_width * yPos) + xPos));
}

void ArcWindow::drawPixel(const int xPos, const int yPos)
{
	if (!inWindow(xPos, yPos))
	{
		return;
	}

	*(_pMemory + (_width * yPos) + xPos) = _currentColor.color();
}

void ArcWindow::fastFloodFill(const int startX, const int endX, const int y, const ArcColor seedColor)
{
	fillSpan(startX, endX, y);
	int newStartX = startX;
	int newEndX   = startX;
	for (; newEndX < endX; newStartX = newEndX)
	{
		if (findspan(newStartX, newEndX, y + 1, seedColor))
		{
			fastFloodFill(newStartX, newEndX, y + 1, seedColor);
		}
		else
		{
			++newEndX;
		}
	}

	newStartX = startX;
	newEndX   = startX;
	for (; newEndX < endX; newStartX = newEndX)
	{
		if (findspan(newStartX, newEndX, y - 1, seedColor))
		{
			fastFloodFill(newStartX, newEndX, y - 1, seedColor);
		}
		else
		{
			++newEndX;
		}
	}
}

void ArcWindow::fillSpan(const int startX, const int endX, const int y)
{
	for (int i = startX; i < endX; ++i)
	{
		drawPixel(i, y);
	}
}

bool ArcWindow::findspan(int& startX, int& endX, const int y, const ArcColor seedColor)
{
	// Ensure the current position is valid.
	if (!inWindow(startX, y) || colorAt(startX, y) != seedColor)
	{
		return false;
	}

	// Find the rightmost point on the span.
	while (endX < _width)
	{
		if (colorAt(endX, y) != seedColor)
		{
			break;
		}
		++endX;
	}

	// Find the leftmost point on the span.
	while (startX > 0)
	{
		if (colorAt(startX - 1, y) != seedColor)
		{
			break;
		}
		--startX;
	}

	return true;
}

bool ArcWindow::inWindow(const int xPos, const int yPos)
{
	return (xPos >= 0 && xPos < _width) && (yPos >= 0 && yPos < _height);
}