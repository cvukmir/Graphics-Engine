#include <numbers>

#include "ArcWindow.h"
#include "ArcColor.h"
#include "ArcEnums.h"
#include "ArcBoundaryCodes.hpp"


// Private Constructor //

ArcWindow::ArcWindow()
	: _backgroundColor  (ArcColor::BLACK)
	, _cameraAtPoint    (0, 0, -1)
	, _cameraEyePoint   (0, 0, 0)
	, _cameraFov        (90.0)
	, _cameraUpVector   (0, 1, 0)
	, _clippingFar      (1.0e+09)
	, _clippingNear     (1.0)
	, _currentColor     (ArcColor::WHITE)
	, _frameNumber      (0)
	, _height           (640)
	, _isRunning        (true)
	, _pCurrentTransform(new ArcTransformMatrixH(ArcMatrix4x4::IDENTITY_MATRIX))
	, _pDepthBuffer     (nullptr)
	, _pMemory          (nullptr)
	, _width            (480)
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

	if (_pDepthBuffer)
	{
		delete(_pDepthBuffer);
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

void                         ArcWindow::backgroundColor(const ArcColor& color)  { _backgroundColor = color; }

void                         ArcWindow::cameraAt(const Arc3DPoint& value)       { _cameraAtPoint = value; }
const Arc3DPoint&            ArcWindow::cameraAt() const                        { return _cameraAtPoint;  }

void                         ArcWindow::cameraEyePoint(const Arc3DPoint& value) { _cameraEyePoint = value; }
const Arc3DPoint&            ArcWindow::cameraEyePoint() const                  { return _cameraEyePoint;  }

void                         ArcWindow::cameraFov(const double value)           { _cameraFov = value; }
const double                 ArcWindow::cameraFov() const                       { return _cameraFov;  }

void                         ArcWindow::cameraUpVector(const ArcVector& value)  { _cameraUpVector = value; }
const ArcVector&             ArcWindow::cameraUpVector() const                  { return _cameraUpVector;  }

void                         ArcWindow::clippingFar(const double value)         { _clippingFar = value; }
const double                 ArcWindow::clippingFar() const                     { return _clippingFar;  }

void                         ArcWindow::clippingNear(const double value)        { _clippingNear = value; }
const double                 ArcWindow::clippingNear() const                    { return _clippingNear;  }

void                         ArcWindow::currentColor(const ArcColor value)      { _currentColor = value; }
const ArcColor               ArcWindow::currentColor() const                    { return _currentColor;  }

void                         ArcWindow::frameNumber(const int value)            { _frameNumber = value; }
const int                    ArcWindow::frameNumber() const                     { return _frameNumber;  }

ArcFrameList::const_iterator ArcWindow::frameBegin() const                      { return _frameList.begin(); }
ArcFrameList::const_iterator ArcWindow::frameEnd()   const                      { return _frameList.end();   }

void                         ArcWindow::isRunning(const bool value)             { _isRunning = value; }
const bool                   ArcWindow::isRunning() const                       { return _isRunning;  }

const UINT32*                ArcWindow::memory() const                          { return _pMemory; }

const int                    ArcWindow::windowHeight() const                    { return _height;  }
void                         ArcWindow::windowHeight(const int value)           { _height = value; }

void                         ArcWindow::windowWidth(const int value)            { _width = value; }
const int                    ArcWindow::windowWidth() const                     { return _width;  }


// Public Methods //

void ArcWindow::clearTransformationMaxtrix()
{
	(*_pCurrentTransform) = ArcMatrix4x4::IDENTITY_MATRIX;
}

void ArcWindow::draw2DCircle(const Arc3DPoint& startPoint, const int radius)
{
	const int startPointX = static_cast<int>(startPoint.x());
	const int startPointY = static_cast<int>(startPoint.y());

	int x = 0;
	int y = radius;
	int p = 1 - radius;

	while (y >= x)
	{
		draw2DPixel(startPointX + x, startPointY + y);
		draw2DPixel(startPointX + y, startPointY + x);
		draw2DPixel(startPointX + y, startPointY - x);
		draw2DPixel(startPointX - x, startPointY + y);
		draw2DPixel(startPointX - x, startPointY - y);
		draw2DPixel(startPointX - y, startPointY - x);
		draw2DPixel(startPointX - y, startPointY + x);
		draw2DPixel(startPointX + x, startPointY - y);

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

void ArcWindow::draw3DCircle(const double radius, const double zMin, const double zMax, const double degrees, PlaneType plane)
{
	const double NSTEPS = degrees;

	switch (plane)
	{
		case (PlaneType::XY): // XY Plane
			linePipeline(Arc3DPoint(radius, 0.0, 0.0), false);
			break;
		case (PlaneType::YZ): // YZ Plane
			linePipeline(Arc3DPoint(0.0, radius, 0.0), false);
			break;
		case (PlaneType::ZX): // ZX Plane
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

		switch (plane)
		{
			case (PlaneType::XY): // XY Plane
				linePipeline(Arc3DPoint(x, y, 0.0), true);
				break;
			case (PlaneType::YZ): // YZ Plane
				linePipeline(Arc3DPoint(0.0, x, y), true);
				break;
			case (PlaneType::ZX): // ZX Plane
				linePipeline(Arc3DPoint(x, 0.0, y), true);
				break;
			default:
				return;
		}
	}
}

void ArcWindow::drawCone(const double height, const double radius, const double degrees)
{
	//Cone (height, radius, thetamax)
	//Starts at origin.
	//	Same as cylinder but drawing points are at x = 0, y = 0, height
	//	Keep them as rectangles and not triangles.Will affect lighting later on.
	
	double theta2Rad = degrees * std::numbers::pi / 180;
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
	linePipeline(Arc3DPoint(-1.0, -1.0,  1.0), false); // Bottom left point
	linePipeline(Arc3DPoint( 1.0, -1.0,  1.0), true);  // Bottom right point
	linePipeline(Arc3DPoint( 1.0,  1.0,  1.0), true);  // Top right point
	linePipeline(Arc3DPoint(-1.0,  1.0,  1.0), true);  // Top left point
//	linePipeline(Arc3DPoint(-1.0, -1.0,  1.0), true);  // Bottom left point

	// Right Face
	linePipeline(Arc3DPoint( 1.0, -1.0,  1.0), false); // Bottom left point
	linePipeline(Arc3DPoint( 1.0, -1.0, -1.0), true);  // Bottom right point
	linePipeline(Arc3DPoint( 1.0,  1.0, -1.0), true);  // ...
	linePipeline(Arc3DPoint( 1.0,  1.0,  1.0), true);
//	linePipeline(Arc3DPoint( 1.0, -1.0,  1.0), true);

	// Far Face
	linePipeline(Arc3DPoint( 1.0, -1.0, -1.0), false);
	linePipeline(Arc3DPoint(-1.0, -1.0, -1.0), true);
	linePipeline(Arc3DPoint(-1.0,  1.0, -1.0), true);
	linePipeline(Arc3DPoint( 1.0,  1.0, -1.0), true);
//	linePipeline(Arc3DPoint( 1.0, -1.0, -1.0), true);

	// Left Face
	linePipeline(Arc3DPoint(-1.0, -1.0, -1.0), false);
	linePipeline(Arc3DPoint(-1.0, -1.0,  1.0), true);
	linePipeline(Arc3DPoint(-1.0,  1.0,  1.0), true);
	linePipeline(Arc3DPoint(-1.0,  1.0, -1.0), true);
//	linePipeline(Arc3DPoint(-1.0, -1.0, -1.0), true);
}

void ArcWindow::drawCylinder(const double radius, const double zmin, const double zmax, const double degrees)
{
	double theta2Rad = degrees * std::numbers::pi / 180;
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

void ArcWindow::drawDisk(const double height, const double radius, const double thetaMax)
{
	const double theta2Rad = thetaMax * std::numbers::pi / 180;
	const double NSTEPS = 360;

	linePipeline(Arc3DPoint(radius, 0.0, height), false);
	for (double i = 1; i < NSTEPS; ++i)
	{
		double theta2 = (i / NSTEPS) * (2 * std::numbers::pi);

		if (theta2 > theta2Rad)
		{
			return;
		}

		double x = radius * cos(theta2);
		double y = radius * sin(theta2);

		linePipeline(Arc3DPoint(x, y, height), true);
	}
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
			draw2DPixel(startPointX, y);
		}
	}
	else if (deltaX == 0 && deltaY < 0)
	{
		// Vertical line that decreases in y.
		for (int y = startPointY; y >= endPointY; --y)
		{
			draw2DPixel(startPointX, y);
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
			draw2DPixel(x - xOffset, y);
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
			draw2DPixel(x, y - yOffset);
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

void ArcWindow::draw3DLine(const Arc3DPointH& startPoint, const Arc3DPointH& endPoint)
{
	const ArcBoundaryCodes BC0 = ArcBoundaryCodes(startPoint);
	const ArcBoundaryCodes BC1 = ArcBoundaryCodes(endPoint);

	if (BC0.kode & BC1.kode)
	{
		return; // Trivial reject
	}

	const uint kode = BC0.kode | BC1.kode;

	if (kode == 0U)
	{
		// Normalize and draw line from H0 to H1
		DDA(ArcTransformMatrixH::clip_to_device(startPoint, _width, _height).toCartesianPoint(),
			ArcTransformMatrixH::clip_to_device(endPoint,   _width, _height).toCartesianPoint());
		return;
	}

	uint   mask   = 1U;
	double alpha  = 0.0;
	double alpha0 = 0.0;
	double alpha1 = 1.0;
	for (uint i = 0; i < 6; ++i, mask <<= 1U)
	{
		if (getBit(kode, i) == 0)
		{
			continue; // No intersection
		}

		alpha = BC0.values[i] / (BC0.values[i] - BC1.values[i]);
		if (BC0.kode & mask)
		{
			// Outside to inside
			alpha0 = max(alpha0, alpha);
		}
		else
		{
			// Inside to outside
			alpha1 = max(alpha1, alpha);
		}

		// If alpha is ever < 0 or > 1, there is an error. (Shouldn�t need to check if the algorithm is correct).
		if (alpha1 < alpha0)
		{
			break; // No line left.
		}
	}

	Arc3DPointH pointH0 = computeParametricLine(startPoint, endPoint, alpha0);
	Arc3DPointH pointH1 = computeParametricLine(startPoint, endPoint, alpha1);

	// Convert to device coordinates
	pointH0 = ArcTransformMatrixH::clip_to_device(pointH0, _width, _height);
	pointH1 = ArcTransformMatrixH::clip_to_device(pointH1, _width, _height);

	// Normalize and draw line from H0 to H1
	DDA(pointH0.toCartesianPoint(), pointH1.toCartesianPoint());
}

void ArcWindow::draw2DPoint(const Arc2DPoint& point)
{
	draw2DPixel(point.x(), point.y());
}

void ArcWindow::draw3DPoint(const Arc3DPoint& point)
{
	pointPipeline(point);
}

void ArcWindow::drawSphere(const double radius, const double zMin, const double zMax, const double degrees)
{
	if (zMin > zMax)
	{
		return;
	}

	draw3DCircle(radius, zMin, zMax, degrees, PlaneType::XY);
	draw3DCircle(radius, zMin, zMax, degrees, PlaneType::YZ);
	draw3DCircle(radius, zMin, zMax, degrees, PlaneType::ZX);
}

void ArcWindow::drawSphere2(double radius, double zMin, double zMax, double degrees)
{
	const uint NSTEPS_LONG = 20U; // Should be multiple of 4 (4 quadrents).
	const uint NSTEPS_LAT  = 10U; // Should be multiple of 2 (2 halves).

	for (uint i = 0U; i < NSTEPS_LONG; ++i)
	{
		// Looping over XZ plane.
		const double phi1 = (static_cast<double>(i)     / static_cast<double>(NSTEPS_LONG)) * (2.0 * std::numbers::pi);
		const double phi2 = (static_cast<double>(i + 1) / static_cast<double>(NSTEPS_LONG)) * (2.0 * std::numbers::pi);

		for (uint j = 0U; j < NSTEPS_LAT; ++j)
		{
			// Looping over XY plane.
			const double theta1 = (static_cast<double>(j)     / static_cast<double>(NSTEPS_LAT)) * (2.0 * std::numbers::pi);
			const double theta2 = (static_cast<double>(j + 1) / static_cast<double>(NSTEPS_LAT)) * (2.0 * std::numbers::pi);

			const Arc3DPoint point1(radius * cos(phi1) * cos(theta1), radius * cos(phi1) * sin(theta1), radius * sin(phi1));
			const Arc3DPoint point2(radius * cos(phi1) * cos(theta2), radius * cos(phi1) * sin(theta2), radius * sin(phi1));
			const Arc3DPoint point3(radius * cos(phi2) * cos(theta2), radius * cos(phi2) * sin(theta2), radius * sin(phi2));
			const Arc3DPoint point4(radius * cos(phi2) * cos(theta1), radius * cos(phi2) * sin(theta1), radius * sin(phi2));

			linePipeline(point1, false);
			linePipeline(point2, true);
			linePipeline(point3, true);
			linePipeline(point4, true);
			linePipeline(point1, true);
		}
	}
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
	uint size = _width * _height;

	if (!_pDepthBuffer)
	{
		_pDepthBuffer = new double[size];
	}

	double* iter = _pDepthBuffer;
	for (uint i = 0; i < size; ++i, ++iter)
	{
		*iter = 1.0;
	}

	_pMemory = new UINT32[size];
	_frameList.push_back(_pMemory);

	fillBackground(_backgroundColor);
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

void ArcWindow::rotateTransformationXY(const double degrees)
{
	_pCurrentTransform->rotate_xy(degrees);
}

void ArcWindow::rotateTransformationYZ(const double degrees)
{
	_pCurrentTransform->rotate_yz(degrees);
}

void ArcWindow::rotateTransformationZX(const double degrees)
{
	_pCurrentTransform->rotate_zx(degrees);
}




// Private Methods //

Arc3DPointH ArcWindow::computeParametricLine(const Arc3DPointH& point1, const Arc3DPointH& point2, const double alpha)
{
	return Arc3DPointH(point1.x() + (alpha * (point2.x() - point1.x())),
		               point1.y() + (alpha * (point2.y() - point1.y())),
		               point1.z() + (alpha * (point2.z() - point1.z())),
		               point1.w() + (alpha * (point2.w() - point1.w())));
}

Arc3DPoint ArcWindow::computeParametricLine(const Arc3DPoint& point1, const Arc3DPoint& point2, const double alpha)
{
	return Arc3DPoint(point1.x() + (alpha * (point2.x() - point1.x())),
		              point1.y() + (alpha * (point2.y() - point1.y())),
		              point1.z() + (alpha * (point2.z() - point1.z())));
}

ArcColor ArcWindow::colorAt(const int xPos, const int yPos)
{
	return ArcColor(*(_pMemory + (_width * yPos) + xPos));
}

void ArcWindow::cyberPunk(double radius)
{
	const uint NSTEPS_LONG = 20U; // Should be multiple of 4 (4 quadrents).
	const uint NSTEPS_LAT = 10U; // Should be multiple of 2 (2 halves).

	for (uint i = 0U; i < NSTEPS_LONG; ++i)
	{
		// Looping over XZ plane.
		const double phi1 = (static_cast<double>(i) / static_cast<double>(NSTEPS_LONG)) * (2.0 * std::numbers::pi);
		const double phi2 = (static_cast<double>(i + 1) / static_cast<double>(NSTEPS_LONG)) * (2.0 * std::numbers::pi);

		for (uint j = 0U; j < NSTEPS_LAT; ++j)
		{
			// Looping over XY plane.
			const double theta1 = (static_cast<double>(j)     / static_cast<double>(NSTEPS_LAT)) * (2.0 * std::numbers::pi);
			const double theta2 = (static_cast<double>(j + 1) / static_cast<double>(NSTEPS_LAT)) * (2.0 * std::numbers::pi);

			const Arc3DPoint point1(radius * cos(phi1) * cos(theta1), radius * cos(phi1) * sin(theta1), radius * sin(phi1));
			const Arc3DPoint point2(radius * cos(phi1) * cos(theta1), radius * cos(phi2) * sin(theta2), radius * sin(phi1));
			const Arc3DPoint point3(radius * cos(phi2) * cos(theta2), radius * cos(phi2) * sin(theta2), radius * sin(phi1));
			const Arc3DPoint point4(radius * cos(phi2) * cos(theta2), radius * cos(phi1) * sin(theta1), radius * sin(phi1));

			linePipeline(point1, false);
			linePipeline(point2, true);
			linePipeline(point3, true);
			linePipeline(point4, true);
			linePipeline(point1, true);
		}
	}
}

void ArcWindow::DDA(const Arc3DPoint& startPoint, const Arc3DPoint& endPoint)
{
	int dx = int(endPoint.x()) - int(startPoint.x()); // Or just floor
	int dy = int(endPoint.y()) - int(startPoint.y());
	const int NSTEPS = max(abs(dx), abs(dy));
	for (int i = 0; i < NSTEPS; ++i)
	{
		double alpha = i / double(NSTEPS);
		draw3DPixel(computeParametricLine(startPoint, endPoint, alpha));
	}
}

void ArcWindow::draw2DPixel(const int xPos, const int yPos)
{
	if (!inWindow(xPos, yPos))
	{
		return;
	}

	*(_pMemory + (_width * yPos) + xPos) = _currentColor.color();
}

void ArcWindow::draw3DPixel(const Arc3DPoint& point)
{
	if (!inWindow(point.x(), point.y()))
	{
		return;
	}

	const uint offset = (_width * int(point.y())) + int(point.x());
	double* depthPosition = _pDepthBuffer + offset;
	
	if (*depthPosition < point.z() || point.z() < 0.0)
	{
		return;
	}
	
	*depthPosition       = point.z();
	*(_pMemory + offset) = _currentColor.color();
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
		draw2DPixel(i, y);
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

const uint ArcWindow::getBit(const uint value, const uint place)
{
	return ((value >> place) & 0x00000001);;
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

	//Arc3DPoint clipCoordinates = mutablePoint.toCartesianPoint();

	if (isDrawing)
	{
		//Arc3DPointH point1 = ArcTransformMatrixH::clip_to_device(_prevClipPoint, _width, _height);
		//Arc3DPointH point2 = ArcTransformMatrixH::clip_to_device(clipCoordinates, _width, _height);
		//draw2DLine(Arc2DPoint(point1.x(), point1.y()), Arc2DPoint(point2.x(), point2.y()));
		draw3DLine(_prevClipPoint, mutablePoint);
	}

	_prevClipPoint = mutablePoint;
}

void ArcWindow::pointPipeline(const Arc3DPoint& point)
{
	Arc3DPointH mutablePoint = point;

	mutablePoint = (*_pCurrentTransform) * mutablePoint;

	mutablePoint = ArcTransformMatrixH::world_to_camera(mutablePoint, _cameraEyePoint, _cameraAtPoint, _cameraUpVector);

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
	//draw2DPixel(mutablePoint.x(), mutablePoint.y());
	draw3DPixel(mutablePoint.toCartesianPoint());
}
