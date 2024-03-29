#include <numbers>

#include "ArcWindow.h"
#include "ArcColor.h"


// Private Constructor //

ArcWindow::ArcWindow()
	: _cameraAtPoint    (0, 0, -1)
	, _cameraEyePoint   (0, 0, 0)
	, _cameraFov        (90.0)
	, _cameraUpVector   (0, 1, 0)
	, _clippingFar      (1.0e+09)
	, _clippingNear     (1.0)
	, _currentColor     (ArcColor::WHITE)
	, _frameNumber      (0)
	, _height           (256)
	, _isRunning        (true)
	, _pCurrentTransform(new ArcTransformMatrixH(ArcMatrix4x4::IDENTITY_MATRIX))
	, _pMemory          (nullptr)
	, _width            (256)
{
}


// Public Destructor //

ArcWindow::~ArcWindow()
{
	for (ArcFrameList::iterator it = _frameList.begin(); it != _frameList.end(); ++it)
	{
		// Destroys _pMemory as well.
		delete(*it);
	}

	if (_pCurrentTransform)
	{
		delete _pCurrentTransform;
	}
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

void              ArcWindow::cameraAt(const Arc3DPoint& value) { _cameraAtPoint = value; }
const Arc3DPoint& ArcWindow::cameraAt() const                  { return _cameraAtPoint;  }

void              ArcWindow::cameraEyePoint(const Arc3DPoint& value) { _cameraEyePoint = value; }
const Arc3DPoint& ArcWindow::cameraEyePoint() const                  { return _cameraEyePoint;  }

void         ArcWindow::cameraFov(const double value) { _cameraFov = value; }
const double ArcWindow::cameraFov() const             { return _cameraFov;  }

void              ArcWindow::cameraUpVector(const ArcVector& value) { _cameraUpVector = value; }
const ArcVector&  ArcWindow::cameraUpVector() const                 { return _cameraUpVector;  }

void          ArcWindow::clippingFar(const double value) { _clippingFar = value; }
const double  ArcWindow::clippingFar() const             { return _clippingFar;  }

void          ArcWindow::clippingNear(const double value) { _clippingNear = value; }
const double  ArcWindow::clippingNear() const             { return _clippingNear; }

void           ArcWindow::currentColor(const ArcColor value) { _currentColor = value; }
const ArcColor ArcWindow::currentColor() const               { return _currentColor;  }

void           ArcWindow::frameNumber(const int value)       { _frameNumber = value; }
const int      ArcWindow::frameNumber() const                { return _frameNumber;  }

ArcFrameList::const_iterator ArcWindow::frameBegin() const         { return _frameList.begin(); }
ArcFrameList::const_iterator ArcWindow::frameEnd()   const         { return _frameList.end();   }

void           ArcWindow::isRunning(const bool value)        { _isRunning = value; }
const bool     ArcWindow::isRunning() const                  { return _isRunning;  }

const UINT32*  ArcWindow::memory() const                     { return _pMemory; }

void           ArcWindow::windowHeight(const int value)      { _height = value; }
const int      ArcWindow::windowHeight() const               { return _height;  }

void           ArcWindow::windowWidth(const int value)       { _width = value; }
const int      ArcWindow::windowWidth() const                { return _width;  }


// Public Methods //

void ArcWindow::draw2DCircle(const Arc3DPoint& startPoint, const int radius)
{
	const int startPointX = static_cast<int>(startPoint.x());
	const int startPointY = static_cast<int>(startPoint.y());

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

void ArcWindow::draw3DCircle(double radius, double zMin, double zMax, double theta, int planeEnum)
{
	const double NSTEPS = theta;

	switch (planeEnum)
	{
	case (0): // XY Plane
		linePipeline(Arc3DPoint(radius, 0.0, 0.0), false);
		break;
	case (1): // YZ Plane
		linePipeline(Arc3DPoint(0.0, radius, 0.0), false);
		break;
	case (2): // ZX Plane
		linePipeline(Arc3DPoint(radius, 0.0, 0.0), false);
		break;
	default:
		return;
	}

	for (double i = 1; i < NSTEPS; ++i)
	{
		double theta2 = (i / NSTEPS) * (2 * std::numbers::pi);
		double x = radius * cos(theta2);
		double y = radius * sin(theta2);

		switch (planeEnum)
		{
		case (0): // XY Plane
			linePipeline(Arc3DPoint(x, y, 0.0), true);
			break;
		case (1): // YZ Plane
			linePipeline(Arc3DPoint(0.0, x, y), true);
			break;
		case (2): // ZX Plane
			linePipeline(Arc3DPoint(x, 0.0, y), true);
			break;
		default:
			return;
		}
	}
}

void ArcWindow::drawCone(double height, double radius, double theta)
{
	//Cone (height, radius, thetamax)
	//Starts at origin.
	//	Same as cylinder but drawing points are at x = 0, y = 0, height
	//	Keep them as rectangles and not triangles.Will affect lighting later on.
	
	double theta2Rad = theta * std::numbers::pi / 180;
	double NSTEPS = 20;

	linePipeline(Arc3DPoint(radius, 0, 0), false);

	Arc3DPoint currDrawPoint;
	Arc3DPoint prevDrawPoint = Arc3DPoint(radius, 0, 0);

	// TODO Remove <= to <. Why is that broken?
	for (double i = 1; i <= NSTEPS; ++i)
	{
		double theta2 = (i / NSTEPS) * (2 * std::numbers::pi);

		if (theta2 > theta2Rad)
		{
			return;
		}

		double x = radius * cos(theta2);
		double y = radius * sin(theta2);

		currDrawPoint = Arc3DPoint(x, y, 0);
		linePipeline(currDrawPoint, true);
		linePipeline(Arc3DPoint(0, 0, height), true);
		linePipeline(prevDrawPoint, true);
		linePipeline(currDrawPoint, false);

		prevDrawPoint = currDrawPoint;
	}
}

void ArcWindow::drawCube()
{
	// Close Face
	linePipeline(Arc3DPoint(-1, -1,  1), false); // Bottom left point
	linePipeline(Arc3DPoint( 1, -1,  1), true);  // Bottom right point
	linePipeline(Arc3DPoint( 1,  1,  1), true);  // Top right point
	linePipeline(Arc3DPoint(-1,  1,  1), true);  // Top left point
//	linePipeline(Arc3DPoint(-1, -1,  1), true);  // Bottom left point

	// Right Face
	linePipeline(Arc3DPoint( 1, -1,  1), false); // Bottom left point
	linePipeline(Arc3DPoint( 1, -1, -1), true);  // Bottom right point
	linePipeline(Arc3DPoint( 1,  1, -1), true);  // ...
	linePipeline(Arc3DPoint( 1,  1,  1), true);
//	linePipeline(Arc3DPoint( 1, -1,  1), true);

	// Far Face
	linePipeline(Arc3DPoint( 1, -1, -1), false);
	linePipeline(Arc3DPoint(-1, -1, -1), true);
	linePipeline(Arc3DPoint(-1,  1, -1), true);
	linePipeline(Arc3DPoint( 1,  1, -1), true);
//	linePipeline(Arc3DPoint( 1, -1, -1), true);

	// Left Face
	linePipeline(Arc3DPoint(-1, -1, -1), false);
	linePipeline(Arc3DPoint(-1, -1,  1), true);
	linePipeline(Arc3DPoint(-1,  1,  1), true);
	linePipeline(Arc3DPoint(-1,  1, -1), true);
//	linePipeline(Arc3DPoint(-1, -1, -1), true);
}

void ArcWindow::drawCylinder(double radius, double zmin, double zmax, double theta)
{
	double theta2Rad = theta * std::numbers::pi / 180;
	double NSTEPS = 20;

	linePipeline(Arc3DPoint(radius, 0, zmin), false);

	Arc3DPoint currDrawPoint;
	Arc3DPoint prevDrawPoint = Arc3DPoint(radius, 0, zmin);

	// TODO Remove <= to <. Why is that broken?
	for (double i = 1; i <= NSTEPS; ++i)
	{
		double theta2 = (i / NSTEPS) * (2 * std::numbers::pi);

		if (theta2 > theta2Rad)
		{
			return;
		}

		double x = radius * cos(theta2);
		double y = radius * sin(theta2);

		currDrawPoint = Arc3DPoint(x, y, zmin);
		linePipeline(currDrawPoint, true);
		linePipeline(Arc3DPoint(x, y, zmax), true);
		linePipeline(Arc3DPoint(prevDrawPoint.x(), prevDrawPoint.y(), zmax), true);
		linePipeline(prevDrawPoint, true);
		linePipeline(currDrawPoint, false);

		prevDrawPoint = currDrawPoint;
	}
}

void ArcWindow::drawDisk(double height, double radius, double thetaMax)
{
	// TODO: This
	// Disk (height, radius, thetamax)

	draw3DCircle(radius, 0, 0, thetaMax, 0);
	draw3DCircle(radius, 0, 0, thetaMax, 0);
}

void ArcWindow::draw2DLine(const Arc2DPoint& startPoint, const Arc2DPoint& endPoint)
{
	const int startPointX = static_cast<int>(startPoint.x());
	const int startPointY = static_cast<int>(startPoint.y());
	const int endPointX   = static_cast<int>(endPoint.x());
	const int endPointY   = static_cast<int>(endPoint.y());

	const int deltaX = endPointX - startPointX;
	const int deltaY = endPointY - startPointY;

	const int twoDeltaX = 2 * abs(deltaX);
	const int twoDeltaY = 2 * abs(deltaY);

	int x = startPointX;
	int y = startPointY;

	if (deltaX == 0 && deltaY > 0)
	{
		// Vertical line that increases in y.
		for (int y = startPointY; y <= endPointY; ++y)
		{
			drawPixel(startPointX, y);
		}
	}
	else if (deltaX == 0 && deltaY < 0)
	{
		// Vertical line that decreases in y.
		for (int y = startPointY; y >= endPointY; --y)
		{
			drawPixel(startPointX, y);
		}
	}
	else if (abs(deltaY) <= abs(deltaX))
	{
		// Line no greater that 45 degrees from x-axis in any direction.
		int       p    = twoDeltaY - abs(deltaX);
		const int endX = deltaX > 0 ? endPointX : endPointX + (2 * abs(deltaX));
		for (; x <= endX; ++x)
		{
			int xOffset = deltaX > 0 ? 0 : 2 * (x - startPointX);
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
		const int endY = deltaY > 0 ? endPointY : endPointY + (2 * abs(deltaY));
		for (; y <= endY; ++y)
		{
			int yOffset = deltaY > 0 ? 0 : 2 * (y - startPointY);
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

void ArcWindow::draw3DLine(const Arc3DLine& line)
{
	linePipeline(line.startPoint(), false);
	linePipeline(line.endPoint(),    true);
}

void ArcWindow::draw2DPoint(const Arc2DPoint& point)
{
	drawPixel(point.x(), point.y());
}

void ArcWindow::draw3DPoint(const Arc3DPoint& point)
{
	pointPipeline(point);
}

void ArcWindow::drawSphere(double radius, double zMin, double zMax, double theta)
{
	// Centered at origin
	// Draw a circle in the x,y plane.
	// Draw a circle in the yz plane.
	// Draw a circle in the zx plane.

	if (zMin > zMax)
	{
		return;
	}

	draw3DCircle(radius, zMin, zMax, theta, 0);
	draw3DCircle(radius, zMin, zMax, theta, 1);
	draw3DCircle(radius, zMin, zMax, theta, 2);
}

void ArcWindow::fill(const Arc2DPoint& startPoint)
{
	const int x = static_cast<int>(startPoint.x());
	const int y = static_cast<int>(startPoint.y());
	const ArcColor seedColor = colorAt(x, y);

	if (seedColor == _currentColor)
	{
		return;
	}

	int newStartX = x;
	int newEndX   = newStartX;

	// Find the span for this first y position.
	findspan(newStartX, newEndX, y, seedColor);

	// Find any spans above this first position.
	fastFloodFill(newStartX, newEndX, y, seedColor);

	// Find any spans below this first position.
	fastFloodFill(newStartX, newEndX, y, seedColor);
}

void ArcWindow::fillBackground(const ArcColor& color)
{
	UINT32* pixel = _pMemory;
	for (int i = 0; i < _width * _height; ++i, ++pixel)
	{
		*pixel = color.color();
	}
}

void ArcWindow::initializeNewFrame()
{
	_pMemory = new UINT32[_width * _height];
	_frameList.push_back(_pMemory);

	fillBackground(ArcColor::BLACK);
}

void ArcWindow::popTransformation()
{
	if (!_transformationStack.empty())
	{
		if (_pCurrentTransform)
		{
			delete(_pCurrentTransform);
		}

		_pCurrentTransform = _transformationStack.top();
		_transformationStack.pop();
	}
}

void ArcWindow::pushTransformation()
{
	_transformationStack.push(new ArcTransformMatrixH(*_pCurrentTransform));
}

void ArcWindow::translateTransformation(const double t1, const double t2, const double t3)
{
	_pCurrentTransform->translate(t1, t2, t3);
}

void ArcWindow::scaleTransformation(const double s1, const double s2, const double s3)
{
	_pCurrentTransform->scale(s1, s2, s3);
}

void ArcWindow::rotateTransformationXY(const double theta)
{
	_pCurrentTransform->rotate_xy(theta);
}

void ArcWindow::rotateTransformationYZ(const double theta)
{
	_pCurrentTransform->rotate_yz(theta);
}

void ArcWindow::rotateTransformationZX(const double theta)
{
	_pCurrentTransform->rotate_zx(theta);
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

bool ArcWindow::inWindow(const int xPos, const int yPos) const
{
	return (xPos >= 0 && xPos < _width) && (yPos >= 0 && yPos < _height);
}

void ArcWindow::linePipeline(const Arc3DPoint& point, const bool isDrawing)
{
	Arc3DPointH mutablePoint(point);

	mutablePoint = (*_pCurrentTransform) * mutablePoint;

	mutablePoint = ArcTransformMatrixH::world_to_camera(mutablePoint, _cameraEyePoint, _cameraAtPoint, _cameraUpVector);

	mutablePoint = ArcTransformMatrixH::camera_to_clip(mutablePoint, _cameraFov, _clippingNear, _clippingFar, static_cast<double>(_width) / static_cast<double>(_height));

	Arc3DPoint clipCoordinates = mutablePoint.toCartesianPoint();

	if (isDrawing)
	{
		Arc3DPointH point1 = ArcTransformMatrixH::clip_to_device(_prevClipPoint, _width, _height);
		Arc3DPointH point2 = ArcTransformMatrixH::clip_to_device(clipCoordinates, _width, _height);
		draw2DLine(Arc2DPoint(point1.x(), point1.y()), Arc2DPoint(point2.x(), point2.y()));
	}

	_prevClipPoint = clipCoordinates;
}

void ArcWindow::pointPipeline(const Arc3DPoint& point)
{
	Arc3DPointH mutablePoint;

	mutablePoint = (*_pCurrentTransform) * mutablePoint;

	mutablePoint = ArcTransformMatrixH::world_to_camera(point, _cameraEyePoint, _cameraAtPoint, _cameraUpVector);

	mutablePoint = ArcTransformMatrixH::camera_to_clip(mutablePoint, _cameraFov, _clippingNear, _clippingFar, static_cast<double>(_width) / static_cast<double>(_height));

	Arc3DPoint clipCoordinates = mutablePoint.toCartesianPoint();

	if (!((clipCoordinates.x() >= 0.0 && clipCoordinates.x() <= 1.0) &&
		  (clipCoordinates.y() >= 0.0 && clipCoordinates.y() <= 1.0) && 
		  (clipCoordinates.z() >= 0.0 && clipCoordinates.z() <= 1.0)))
	{
		// Not in clipping plane, will not be shown.
		return;
	}

	mutablePoint = ArcTransformMatrixH::clip_to_device(clipCoordinates, _width, _height);
	drawPixel(mutablePoint.x(), mutablePoint.y());
}
