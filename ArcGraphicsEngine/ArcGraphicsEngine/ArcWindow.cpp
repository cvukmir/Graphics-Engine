#include <numbers>

#include "ArcWindow.h"
#include "ArcColor.h"
#include "ArcEnums.h"
#include "ArcBoundaryCodes.hpp"
#include "Arc3DAttributedPoint.h"
#include "ArcMath.h"

// Private Constructor //

ArcWindow::ArcWindow()
	: _ambientCoefficient (1.0)
	, _ambientLight       (new ArcAmbientLight())
	, _backgroundColor    (ArcColor::BLACK)
	, _cameraAtPoint      (0, 0, -1)
	, _cameraEyePoint     (0, 0, 0)
	, _cameraFov          (90.0)
	, _cameraUpVector     (0, 1, 0)
	, _clippingFar        (1.0e+09)
	, _clippingNear       (1.0)
	, _currentColor       (ArcColor::WHITE)
	, _diffuseCoefficient (0.0)
	, _edgeTable          (nullptr)
	, _frameNumber        (0)
	, _height             (640)
	, _isRunning          (true)
	, _pCurrentTransform  (new ArcTransformMatrixH(ArcMatrix4x4::IDENTITY_MATRIX))
	, _pDepthBuffer       (nullptr)
	, _pMemory            (nullptr)
	, _specularCoefficient(0.0)
	, _surfaceColor       (ArcColor::WHITE)
	, _width              (480)
	
	, _vertexColorFlag     (false)
	, _vertexNormalFlag    (false)
	, _vertexTextureFlag   (false)
	, _useInterpolationFlag(true)
	, _specularColor       (ArcColor::WHITE)
	, _specularExponent    (10.0)
	, _pSurfaceShader      (matte)
	, _pNormalTransform    (new ArcTransformMatrixH(ArcMatrix4x4::IDENTITY_MATRIX))
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

	while (!_transformationStack.empty())
	{
		delete(_transformationStack.top());
		_transformationStack.pop();
	}

	while (!_normalTransformationStack.empty())
	{
		delete(_transformationStack.top());
		_transformationStack.pop();
	}

	for (ArcFarLightList::iterator it = _farLightList.begin(); it != _farLightList.end(); ++it)
	{
		delete(*it);
	}

	for (ArcPointLightList::iterator it = _pointLightList.begin(); it != _pointLightList.end(); ++it)
	{
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

	if (_edgeTable)
	{
		delete(_edgeTable);
	}

	if (_ambientLight)
	{
		delete(_ambientLight);
	}

	if (_pNormalTransform)
	{
		delete(_pNormalTransform);
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

void                         ArcWindow::ambientCoefficient(double value)        { _ambientCoefficient = value; }
const double                 ArcWindow::ambientCoefficient() const              { return _ambientCoefficient; }

ArcAmbientLight*             ArcWindow::ambientLight() const                    { return _ambientLight;  }

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

void                         ArcWindow::currentColor(const ArcColor value)      { _currentColor = value; _surfaceColor = value; }
const ArcColor               ArcWindow::currentColor() const                    { return _currentColor;  }

void                         ArcWindow::diffuseCoefficient(double value)        { _diffuseCoefficient = value;}
const double                 ArcWindow::diffuseCoefficient() const              { return _diffuseCoefficient; }

ArcFarLightList&             ArcWindow::farLightList()                          { return _farLightList; }

void                         ArcWindow::frameNumber(const int value)            { _frameNumber = value; }
const int                    ArcWindow::frameNumber() const                     { return _frameNumber;  }

ArcFrameList::const_iterator ArcWindow::frameBegin() const                      { return _frameList.begin(); }
ArcFrameList::const_iterator ArcWindow::frameEnd()   const                      { return _frameList.end();   }

void                         ArcWindow::isRunning(const bool value)             { _isRunning = value; }
const bool                   ArcWindow::isRunning() const                       { return _isRunning;  }

const UINT32*                ArcWindow::memory() const                          { return _pMemory; }

ArcPointLightList&           ArcWindow::pointLightList()                        { return _pointLightList; }

void                         ArcWindow::specularCoefficient(double value)       { _specularCoefficient = value;}
const double                 ArcWindow::specularCoefficient() const             { return _specularCoefficient; }

void                         ArcWindow::specularColor(const ArcColor value)     { _specularColor = value; }
const ArcColor               ArcWindow::specularColor() const                   { return _specularColor;  }

void                         ArcWindow::specularExponent(double value)          { _specularExponent = value;}
const double                 ArcWindow::specularExponent() const                { return _specularExponent; }

void                         ArcWindow::surfaceColor(const ArcColor value)      { _surfaceColor = value; }
const ArcColor               ArcWindow::surfaceColor() const                    { return _surfaceColor;  }

void                         ArcWindow::useInterpolation(const bool value)      { _useInterpolationFlag = value; }
const bool                   ArcWindow::useInterpolation() const                { return _useInterpolationFlag; }

void ArcWindow::vertexNormalFlag(const bool value)
{
	_vertexNormalFlag = value;
}

const int                    ArcWindow::windowHeight() const                    { return _height;  }
void                         ArcWindow::windowHeight(const int value)           { _height = value; }

void                         ArcWindow::windowWidth(const int value)            { _width = value; }
const int                    ArcWindow::windowWidth() const                     { return _width;  }


// Public Methods //

void ArcWindow::clearTransformationMaxtrix()
{
	(*_pCurrentTransform) = ArcMatrix4x4::IDENTITY_MATRIX;
	(*_pNormalTransform)  = ArcMatrix4x4::IDENTITY_MATRIX;
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

void ArcWindow::draw2DPixel(const int xPos, const int yPos)
{
	if (!inWindow(xPos, yPos))
	{
		return;
	}

	*(_pMemory + (_width * yPos) + xPos) = _currentColor.colorToUint();
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
	*(_pMemory + offset) = _currentColor.colorToUint();
}

void ArcWindow::draw3DPixel(const Arc3DPoint& point, const ArcColor& color)
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

	*depthPosition = point.z();
	if (point.x() == 392.0 && point.y() == 271.0)
	{
		bool test = true;
	}
	uint* mem = (_pMemory + offset);
	*mem = color.colorToUint();
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

	_vertexColorFlag   = false;
	_vertexTextureFlag = false;
	_vertexNormalFlag  = true;
	
	const double theta2Rad = degrees * std::numbers::pi / 180;
	const double NSTEPS = 20;
	const double vecAngleZ = (radius * radius) / height;

	linePipeline(Arc3DPoint(radius, 0, 0), false);

	Arc3DPoint currDrawPoint;
	Arc3DPoint coneTopPoint(0, 0, height);
	Arc3DPoint prevDrawPoint = Arc3DPoint(radius, 0.0, 0.0);

	ArcVector currDrawVector;
	ArcVector prevDrawVector = ArcVector(radius, 0.0, vecAngleZ);

	Arc3DAttributedPointList pointList;

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
		currDrawVector = ArcVector(x, y, vecAngleZ);

		pointList.push_back(new Arc3DAttributedPoint(currDrawPoint, currDrawVector));
		pointList.push_back(new Arc3DAttributedPoint(coneTopPoint,  currDrawVector));
		pointList.push_back(new Arc3DAttributedPoint(coneTopPoint,  prevDrawVector));
		pointList.push_back(new Arc3DAttributedPoint(prevDrawPoint, prevDrawVector));

		drawPolygon(pointList);

		for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			delete(*it);
		}

		pointList.clear();

		prevDrawPoint = currDrawPoint;
		prevDrawVector = currDrawVector;
	}
}

void ArcWindow::drawCube()
{
	// Using Wireframe //
//	// Close Face
//	linePipeline(Arc3DPoint(-1.0, -1.0,  1.0), false); // Bottom left point
//	linePipeline(Arc3DPoint( 1.0, -1.0,  1.0), true);  // Bottom right point
//	linePipeline(Arc3DPoint( 1.0,  1.0,  1.0), true);  // Top right point
//	linePipeline(Arc3DPoint(-1.0,  1.0,  1.0), true);  // Top left point
////	linePipeline(Arc3DPoint(-1.0, -1.0,  1.0), true);  // Bottom left point
//
//	// Right Face
//	linePipeline(Arc3DPoint( 1.0, -1.0,  1.0), false); // Bottom left point
//	linePipeline(Arc3DPoint( 1.0, -1.0, -1.0), true);  // Bottom right point
//	linePipeline(Arc3DPoint( 1.0,  1.0, -1.0), true);  // ...
//	linePipeline(Arc3DPoint( 1.0,  1.0,  1.0), true);
////	linePipeline(Arc3DPoint( 1.0, -1.0,  1.0), true);
//
//	// Far Face
//	linePipeline(Arc3DPoint( 1.0, -1.0, -1.0), false);
//	linePipeline(Arc3DPoint(-1.0, -1.0, -1.0), true);
//	linePipeline(Arc3DPoint(-1.0,  1.0, -1.0), true);
//	linePipeline(Arc3DPoint( 1.0,  1.0, -1.0), true);
////	linePipeline(Arc3DPoint( 1.0, -1.0, -1.0), true);
//
//	// Left Face
//	linePipeline(Arc3DPoint(-1.0, -1.0, -1.0), false);
//	linePipeline(Arc3DPoint(-1.0, -1.0,  1.0), true);
//	linePipeline(Arc3DPoint(-1.0,  1.0,  1.0), true);
//	linePipeline(Arc3DPoint(-1.0,  1.0, -1.0), true);
////	linePipeline(Arc3DPoint(-1.0, -1.0, -1.0), true);

	_vertexColorFlag   = false;
	_vertexTextureFlag = false;
	_vertexNormalFlag  = false; // Don't have the normals for each face due to properties of a cube.

	// Using solid fill //
	Arc3DPoint origin(0, 0, 0);

	Arc3DPoint vertex1;
	Arc3DPoint vertex2;
	Arc3DPoint vertex3;
	Arc3DPoint vertex4;

	Arc3DAttributedPointList pointList;

	// Close Face
	vertex1 = Arc3DPoint(-1.0, -1.0,  1.0);
	vertex2 = Arc3DPoint( 1.0, -1.0,  1.0);
	vertex3 = Arc3DPoint( 1.0,  1.0,  1.0);
	vertex4 = Arc3DPoint(-1.0,  1.0,  1.0);

	pointList.push_back(new Arc3DAttributedPoint(vertex1));
	pointList.push_back(new Arc3DAttributedPoint(vertex2));
	pointList.push_back(new Arc3DAttributedPoint(vertex3));
	pointList.push_back(new Arc3DAttributedPoint(vertex4));

	drawPolygon(pointList);

	for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
	{
		delete(*it);
	}

	pointList.clear();

	// Right Face
	vertex1 = Arc3DPoint( 1.0, -1.0,  1.0);
	vertex2 = Arc3DPoint( 1.0, -1.0, -1.0);
	vertex3 = Arc3DPoint( 1.0,  1.0, -1.0);
	vertex4 = Arc3DPoint( 1.0,  1.0,  1.0);

	pointList.push_back(new Arc3DAttributedPoint(vertex1));
	pointList.push_back(new Arc3DAttributedPoint(vertex2));
	pointList.push_back(new Arc3DAttributedPoint(vertex3));
	pointList.push_back(new Arc3DAttributedPoint(vertex4));

	drawPolygon(pointList);

	for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
	{
		delete(*it);
	}

	pointList.clear();

	// Far Face
	vertex1 = Arc3DPoint( 1.0, -1.0, -1.0);
	vertex2 = Arc3DPoint(-1.0, -1.0, -1.0);
	vertex3 = Arc3DPoint(-1.0,  1.0, -1.0);
	vertex4 = Arc3DPoint( 1.0,  1.0, -1.0);

	pointList.push_back(new Arc3DAttributedPoint(vertex1));
	pointList.push_back(new Arc3DAttributedPoint(vertex2));
	pointList.push_back(new Arc3DAttributedPoint(vertex3));
	pointList.push_back(new Arc3DAttributedPoint(vertex4));

	drawPolygon(pointList);

	for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
	{
		delete(*it);
	}

	pointList.clear();

	// Left Face
	vertex1 = Arc3DPoint(-1.0, -1.0, -1.0);
	vertex2 = Arc3DPoint(-1.0, -1.0,  1.0);
	vertex3 = Arc3DPoint(-1.0,  1.0,  1.0);
	vertex4 = Arc3DPoint(-1.0,  1.0, -1.0);

	pointList.push_back(new Arc3DAttributedPoint(vertex1));
	pointList.push_back(new Arc3DAttributedPoint(vertex2));
	pointList.push_back(new Arc3DAttributedPoint(vertex3));
	pointList.push_back(new Arc3DAttributedPoint(vertex4));

	drawPolygon(pointList);

	for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
	{
		delete(*it);
	}

	pointList.clear();
}

void ArcWindow::drawCylinder(const double radius, const double zmin, const double zmax, const double degrees)
{
	_vertexColorFlag   = false;
	_vertexTextureFlag = false;
	_vertexNormalFlag  = true;

	const double theta2Rad = degrees * std::numbers::pi / 180;
	const double NSTEPS = 20;

	Arc3DPoint currDrawPoint;
	Arc3DPoint oppCurrDrawPoint;
	ArcVector  currVector;
	Arc3DPoint prevDrawPoint    = Arc3DPoint(radius, 0.0, zmin);
	Arc3DPoint prevOppDrawPoint = Arc3DPoint(radius, 0.0, zmax);
	ArcVector  prevVector       =  ArcVector(radius, 0.0, 0.0);


	Arc3DAttributedPointList pointList;

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

		currDrawPoint    = Arc3DPoint(x, y, zmin);
		oppCurrDrawPoint = Arc3DPoint(x, y, zmax);
		currVector       =  ArcVector(x, y, 0.0);

		pointList.push_back(new Arc3DAttributedPoint(currDrawPoint,    currVector));
		pointList.push_back(new Arc3DAttributedPoint(oppCurrDrawPoint, currVector));
		pointList.push_back(new Arc3DAttributedPoint(prevOppDrawPoint, prevVector));
		pointList.push_back(new Arc3DAttributedPoint(prevDrawPoint,    prevVector));

		drawPolygon(pointList);

		for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			delete(*it);
		}

		pointList.clear();

		prevDrawPoint    = currDrawPoint;
		prevOppDrawPoint = oppCurrDrawPoint;
		prevVector       = currVector;
	}
}

void ArcWindow::drawDisk(const double height, const double radius, const double thetaMax)
{
	_vertexColorFlag   = false;
	_vertexTextureFlag = false;
	_vertexNormalFlag  = true;

	double theta2Rad = thetaMax * std::numbers::pi / 180;
	double NSTEPS = 20;

	Arc3DPoint currDrawPoint;
	Arc3DPoint prevDrawPoint = Arc3DPoint(radius, 0, height);
	const Arc3DPoint diskCenter    = Arc3DPoint(0, 0, height);
	const ArcVector  diskVector    = ArcVector(0.0, 0.0, 1.0);

	Arc3DAttributedPointList pointList;

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

		currDrawPoint = Arc3DPoint(x, y, height);

		pointList.push_back(new Arc3DAttributedPoint(currDrawPoint, diskVector));
		pointList.push_back(new Arc3DAttributedPoint(diskCenter,    diskVector));
		pointList.push_back(new Arc3DAttributedPoint(diskCenter,    diskVector));
		pointList.push_back(new Arc3DAttributedPoint(prevDrawPoint, diskVector));

		drawPolygon(pointList);

		for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			delete(*it);
		}

		pointList.clear();

		prevDrawPoint = currDrawPoint;
	}
}

bool ArcWindow::drawPolygon(const Arc3DAttributedPointList& pointList)
{
	if (pointList.size() < 3U)
	{
		// A polygon is defined to have at least three sides...
		return false;
	}

	_surfaceNormal = ArcVector(pointList[0]->position(), pointList[1]->position()).crossProduct(ArcVector(pointList[1]->position(), pointList[2]->position()));

	Arc3DAttributedPointList vertex_list;

	Arc3DAttributedPointList::const_reverse_iterator itEnd = pointList.rbegin();
	for (Arc3DAttributedPointList::const_iterator it = pointList.begin(); (*it) != (*itEnd); ++it)
	{
		if (!polygonPipeline(vertex_list, *it, false))
		{
			return false;
		}
	}

	return polygonPipeline(vertex_list, *itEnd, true);
}

void ArcWindow::drawHaloRing(double radius, double degrees, double width, double thickness)
{
	_vertexColorFlag   = false;
	_vertexTextureFlag = false;
	_vertexNormalFlag  = true;

	const Arc3DPoint origin(0, 0, 0);
	Arc3DAttributedPointList pointList;

	const double NSTEPS = 100;
	const double halfWidth = width / 2.0;

	const double innerRadius = radius - thickness;

	double theta = 0.0;
	double prevOutsideX = radius * cos(theta);
	double prevOutsideY = radius * sin(theta);

	double prevInsideX = innerRadius * cos(theta);
	double prevInsideY = innerRadius * sin(theta);

	for (uint i = 1U; i <= static_cast<uint>(NSTEPS); ++i)
	{
		theta = (i / NSTEPS) * (2 * std::numbers::pi);

		// Outside "back" face

		double currOutsideX = radius * cos(theta);
		double currOutsideY = radius * sin(theta);

		const Arc3DPoint outPoint1(prevOutsideX, prevOutsideY, halfWidth);
		const Arc3DPoint outPoint2(currOutsideX, currOutsideY, halfWidth);
		const Arc3DPoint outPoint3(currOutsideX, currOutsideY, -halfWidth);
		const Arc3DPoint outPoint4(prevOutsideX, prevOutsideY, -halfWidth);
		
		pointList.push_back(new Arc3DAttributedPoint(outPoint1, ArcVector(origin, outPoint1)));
		pointList.push_back(new Arc3DAttributedPoint(outPoint2, ArcVector(origin, outPoint2)));
		pointList.push_back(new Arc3DAttributedPoint(outPoint3, ArcVector(origin, outPoint3)));
		pointList.push_back(new Arc3DAttributedPoint(outPoint4, ArcVector(origin, outPoint4)));
		
		drawPolygon(pointList);
		
		for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			delete(*it);
		}

		pointList.clear();

		// Inside face
		double currInsideX = innerRadius * cos(theta);
		double currInsideY = innerRadius * sin(theta);

		const Arc3DPoint inPoint1(prevInsideX, prevInsideY, halfWidth);
		const Arc3DPoint inPoint2(currInsideX, currInsideY, halfWidth);
		const Arc3DPoint inPoint3(currInsideX, currInsideY, -halfWidth);
		const Arc3DPoint inPoint4(prevInsideX, prevInsideY, -halfWidth);
		
		pointList.push_back(new Arc3DAttributedPoint(inPoint1, ArcVector(inPoint1, origin)));
		pointList.push_back(new Arc3DAttributedPoint(inPoint2, ArcVector(inPoint2, origin)));
		pointList.push_back(new Arc3DAttributedPoint(inPoint3, ArcVector(inPoint3, origin)));
		pointList.push_back(new Arc3DAttributedPoint(inPoint4, ArcVector(inPoint4, origin)));
		
		drawPolygon(pointList);
		
		for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			delete(*it);
		}

		pointList.clear();

		prevOutsideX = currOutsideX;
		prevOutsideY = currOutsideY;

		prevInsideX = currInsideX;
		prevInsideY = currInsideY;

		// Left face (-thickness)
		pointList.push_back(new Arc3DAttributedPoint(outPoint3, ArcVector(outPoint2, outPoint3)));
		pointList.push_back(new Arc3DAttributedPoint(outPoint4, ArcVector(outPoint1, outPoint4)));
		pointList.push_back(new Arc3DAttributedPoint(inPoint4,  ArcVector(inPoint1, inPoint4)));
		pointList.push_back(new Arc3DAttributedPoint(inPoint3,  ArcVector(inPoint2, inPoint3)));

		drawPolygon(pointList);

		for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			delete(*it);
		}

		pointList.clear();

		// Right Face (+thickness)
		pointList.push_back(new Arc3DAttributedPoint(outPoint1, ArcVector(outPoint4, outPoint1)));
		pointList.push_back(new Arc3DAttributedPoint(outPoint2, ArcVector(outPoint3, outPoint2)));
		pointList.push_back(new Arc3DAttributedPoint(inPoint2,  ArcVector(inPoint3, inPoint2)));
		pointList.push_back(new Arc3DAttributedPoint(inPoint1,  ArcVector(inPoint4, inPoint1)));

		drawPolygon(pointList);

		for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
		{
			delete(*it);
		}

		pointList.clear();

		prevOutsideX = currOutsideX;
		prevOutsideY = currOutsideY;

		prevInsideX = currInsideX;
		prevInsideY = currInsideY;
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
			alpha1 = min(alpha1, alpha);
		}

		// If alpha is ever < 0 or > 1, there is an error. (Shouldn�t need to check if the algorithm is correct).
		if (alpha1 < alpha0)
		{
			break; // No line left.
		}
	}

	Arc3DPointH pointH0 = Arc3DPointH::interpolateTo(startPoint, endPoint, alpha0);
	Arc3DPointH pointH1 = Arc3DPointH::interpolateTo(startPoint, endPoint, alpha1);

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
	_vertexColorFlag   = false;
	_vertexTextureFlag = false;
	_vertexNormalFlag  = true;

	const uint NSTEPS_LONG = 20U; // Should be multiple of 4 (4 quadrents).
	const uint NSTEPS_LAT  = 10U; // Should be multiple of 2 (2 halves).

	const Arc3DPoint origin(0, 0, 0);
	Arc3DAttributedPointList pointList;

	for (uint i = 0U; i < NSTEPS_LAT; ++i)
	{
		// Looping over XZ plane.
		const double phi1 = ((static_cast<double>(i)     / static_cast<double>(NSTEPS_LAT)) * std::numbers::pi) - (std::numbers::pi / 2.0);
		const double phi2 = ((static_cast<double>(i + 1) / static_cast<double>(NSTEPS_LAT)) * std::numbers::pi) - (std::numbers::pi / 2.0);

		for (uint j = 0U; j < NSTEPS_LONG; ++j)
		{
			// Looping over XY plane.
			const double theta1 = (static_cast<double>(j)     / static_cast<double>(NSTEPS_LONG)) * (2.0 * std::numbers::pi);
			const double theta2 = (static_cast<double>(j + 1) / static_cast<double>(NSTEPS_LONG)) * (2.0 * std::numbers::pi);

			const Arc3DPoint point1(radius * cos(phi1) * cos(theta1), radius * cos(phi1) * sin(theta1), radius * sin(phi1));
			const Arc3DPoint point2(radius * cos(phi1) * cos(theta2), radius * cos(phi1) * sin(theta2), radius * sin(phi1));
			const Arc3DPoint point3(radius * cos(phi2) * cos(theta2), radius * cos(phi2) * sin(theta2), radius * sin(phi2));
			const Arc3DPoint point4(radius * cos(phi2) * cos(theta1), radius * cos(phi2) * sin(theta1), radius * sin(phi2));
		
			pointList.push_back(new Arc3DAttributedPoint(point1, ArcVector(origin, point1)));
			pointList.push_back(new Arc3DAttributedPoint(point2, ArcVector(origin, point2)));
			pointList.push_back(new Arc3DAttributedPoint(point3, ArcVector(origin, point3)));
			pointList.push_back(new Arc3DAttributedPoint(point4, ArcVector(origin, point4)));
		
			drawPolygon(pointList);
		
			for (Arc3DAttributedPointList::iterator it = pointList.begin(); it != pointList.end(); ++it)
			{
				delete(*it);
			}

			pointList.clear();
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
	uint memoryColor = color.colorToUint();
	UINT32* pixel = _pMemory;
	for (int i = 0; i < _width * _height; ++i, ++pixel)
	{
		*pixel = memoryColor;
	}
}

void ArcWindow::initializeNewFrame()
{
	uint size = _width * _height;

	if (!_pDepthBuffer)
	{
		_pDepthBuffer = new double[size];
		_edgeTable    = new ArcEdgeTable(_height);
	}

	double* iter = _pDepthBuffer;
	for (uint i = 0; i < size; ++i, ++iter)
	{
		*iter = 1.0;
	}

	_pMemory = new UINT32[size];
	_frameList.push_back(_pMemory);

	fillBackground(_backgroundColor);

	// Clear the light lists.
	for (ArcFarLightList::iterator it = _farLightList.begin(); it != _farLightList.end(); ++it)
	{
		delete(*it);
	}

	_farLightList.clear();

	for (ArcPointLightList::iterator it = _pointLightList.begin(); it != _pointLightList.end(); ++it)
	{
		delete(*it);
	}

	_pointLightList.clear();

	// Regenerate the ambient light (NOT DELETING ATM)
//	if (_ambientLight)
//	{
//		delete _ambientLight;
//	}
//
//	_ambientLight = new ArcAmbientLight();
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

	if (!_normalTransformationStack.empty())
	{
		if (_pNormalTransform)
		{
			delete(_pNormalTransform);
		}

		_pNormalTransform = _normalTransformationStack.top();
		_normalTransformationStack.pop();
	}
}

void ArcWindow::pushTransformation()
{
	_transformationStack.push(new ArcTransformMatrixH(*_pCurrentTransform));
	_normalTransformationStack.push(new ArcTransformMatrixH(*_pNormalTransform));
}

void ArcWindow::translateTransformation(const double t1, const double t2, const double t3)
{
	_pCurrentTransform->translate(t1, t2, t3);
	// Don't need to multiply the normal transformation since they are not affected by translates.
}

void ArcWindow::scaleTransformation(const double s1, const double s2, const double s3)
{
	_pCurrentTransform->scale(s1, s2, s3);
	(*_pNormalTransform) * ArcTransformMatrixH::scaleInverseMatrix(s1, s2, s3);
}

void ArcWindow::setMaterialType(const std::string& type)
{
	if (type == "\"matte\"")
	{
		_pSurfaceShader = matte;
	}
	else if (type == "\"metal\"")
	{
		_pSurfaceShader = metal;
	}
	else if (type == "\"plastic\"")
	{
		_pSurfaceShader = plastic;
	}
}

void ArcWindow::rotateTransformationXY(const double degrees)
{
	_pCurrentTransform->rotateXY(degrees);
	(*_pNormalTransform) * ArcTransformMatrixH::rotateXYMatrix(degrees);
}

void ArcWindow::rotateTransformationYZ(const double degrees)
{
	_pCurrentTransform->rotateYZ(degrees);
	(*_pNormalTransform) * ArcTransformMatrixH::rotateYZMatrix(degrees);
}

void ArcWindow::rotateTransformationZX(const double degrees)
{
	_pCurrentTransform->rotateZX(degrees);
	(*_pNormalTransform) * ArcTransformMatrixH::rotateZXMatrix(degrees);
}




// Private Methods //

void ArcWindow::clipAPoint(Arc3DAttributedPoint* pPoint, BoundaryType boundary, Arc3DAttributedPointList& firstPointList, Arc3DAttributedPointList& lastPointList, bool faceSeenList[6], Arc3DAttributedPointList& outputArray)
{
	const uint b = static_cast<uint>(boundary);
	if (faceSeenList[b] == false)
	{
		firstPointList[b] = pPoint;
		faceSeenList[b] = true;
	}
	else
	{
		// Previous point exists
		if (cross(pPoint, lastPointList[b], boundary))
		{
			Arc3DAttributedPoint* ipt = intersect(pPoint, lastPointList[b], boundary);
			// send ipt to the next stage of the pipeline or to the output array depending on b, i.e.
			if (boundary != BoundaryType::Last)
			{
				clipAPoint(ipt, static_cast<BoundaryType>(b + 1U), firstPointList, lastPointList, faceSeenList, outputArray);
			}
			else
			{
				outputArray.push_back(ipt);
			}
		}
	}

	// Save the most recent vertex seen at this stage.
	lastPointList[b] = pPoint;

	if (inside(pPoint, boundary))
	{
		if (boundary != BoundaryType::Last)
		{
			clipAPoint(pPoint, static_cast<BoundaryType>(b + 1U), firstPointList, lastPointList, faceSeenList, outputArray);
		}
		else
		{
			outputArray.push_back(pPoint);
		}
	}
}

void ArcWindow::clipLastPoint(Arc3DAttributedPointList& firstPointList, Arc3DAttributedPointList& lastPointList, bool faceSeenList[6], Arc3DAttributedPointList& outputArray)
{
	for (uint i = 0; i <= static_cast<uint>(BoundaryType::Last); ++i)
	{
		if (firstPointList[i] != nullptr && cross(firstPointList[i], lastPointList[i], static_cast<BoundaryType>(i)))
		{
			Arc3DAttributedPoint* ipt = intersect(lastPointList[i], firstPointList[i], static_cast<BoundaryType>(i));

			if (static_cast<BoundaryType>(i) != BoundaryType::Last)
			{
				clipAPoint(ipt, static_cast<BoundaryType>(i + 1U), firstPointList, lastPointList, faceSeenList, outputArray);
			}
			else
			{
				outputArray.push_back(ipt);
			}
		}
	}
}

ArcColor ArcWindow::colorAt(const int xPos, const int yPos)
{
	return ArcColor(*(_pMemory + (_width * yPos) + xPos));
}

bool ArcWindow::cross(Arc3DAttributedPoint* pPoint1, Arc3DAttributedPoint* pPoint2, BoundaryType boundary)
{
	return inside(pPoint1, boundary) != inside(pPoint2, boundary);
}

void ArcWindow::cyberPunk(double radius)
{
	// THIS IS A JOKE/BROKEN METHOD //
	// DO NOT USE!! //
	const uint NSTEPS_LONG = 20U; // Should be multiple of 4 (4 quadrents).
	const uint NSTEPS_LAT = 10U;  // Should be multiple of 2 (2 halves).

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
	for (int i = 0; i <= NSTEPS; ++i)
	{
		double alpha = i / double(NSTEPS);
		draw3DPixel(Arc3DPoint::interpolateTo(startPoint, endPoint, alpha));
	}
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

Arc3DAttributedPoint* ArcWindow::intersect(Arc3DAttributedPoint* pPoint1, Arc3DAttributedPoint* pPoint2, BoundaryType boundary)
{
	// t = BC0 / (BC0 - BC1) -> w0-x0 / (w0-x0) - (w1-x1)
	double alpha = 0.0;

	switch (boundary)
	{
		case (BoundaryType::Left):
			alpha = pPoint1->position().x() / (pPoint1->position().x() - pPoint2->position().x());
			return new Arc3DAttributedPoint(Arc3DAttributedPoint::interpolateTo(*pPoint1, *pPoint2, alpha));
		case (BoundaryType::Right):
			alpha = (pPoint1->position().w() - pPoint1->position().x()) / ((pPoint1->position().w() - pPoint1->position().x()) - (pPoint2->position().w() - pPoint2->position().x()));
			return new Arc3DAttributedPoint(Arc3DAttributedPoint::interpolateTo(*pPoint1, *pPoint2, alpha));
		case (BoundaryType::Bottom):
			alpha = pPoint1->position().y() / (pPoint1->position().y() - pPoint2->position().y());
			return new Arc3DAttributedPoint(Arc3DAttributedPoint::interpolateTo(*pPoint1, *pPoint2, alpha));
		case (BoundaryType::Top):
			alpha = (pPoint1->position().w() - pPoint1->position().y()) / ((pPoint1->position().w() - pPoint1->position().y()) - (pPoint2->position().w() - pPoint2->position().y()));
			return new Arc3DAttributedPoint(Arc3DAttributedPoint::interpolateTo(*pPoint1, *pPoint2, alpha));
		case (BoundaryType::Front):
			alpha = pPoint1->position().z() / (pPoint1->position().z() - pPoint2->position().z());
			return new Arc3DAttributedPoint(Arc3DAttributedPoint::interpolateTo(*pPoint1, *pPoint2, alpha));
		case (BoundaryType::Back):
			alpha = (pPoint1->position().w() - pPoint1->position().z()) / ((pPoint1->position().w() - pPoint1->position().z()) - (pPoint2->position().w() - pPoint2->position().z()));
			return new Arc3DAttributedPoint(Arc3DAttributedPoint::interpolateTo(*pPoint1, *pPoint2, alpha));
		default:
			break;
	}

	return nullptr;
}

bool ArcWindow::inside(Arc3DAttributedPoint* pPoint, BoundaryType boundary)
{
	switch (boundary)
	{
		case (BoundaryType::Left):
			return !(pPoint->position().x() < 0.0);
		case (BoundaryType::Right):
			return !(pPoint->position().w() - pPoint->position().x() < 0.0);
		case (BoundaryType::Bottom):
			return !(pPoint->position().y() < 0.0);
		case (BoundaryType::Top):
			return !(pPoint->position().w() - pPoint->position().y() < 0.0);
		case (BoundaryType::Front):
			return !(pPoint->position().z() < 0.0);
		case (BoundaryType::Back):
			return !(pPoint->position().w() - pPoint->position().z() < 0.0);
		default:
			break;
	}

	return false;
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

Arc3DAttributedPointList ArcWindow::polygonClip(Arc3DAttributedPointList& pointList)
{
	Arc3DAttributedPointList outputArray;
	Arc3DAttributedPointList firstPointList(6);
	Arc3DAttributedPointList lastPointList(6);
	bool                     faceSeenList[6] = { false };

	Arc3DAttributedPointList vertex_list;

	Arc3DAttributedPointList::const_iterator itEnd = pointList.end();
	for (Arc3DAttributedPointList::const_iterator it = pointList.begin(); it != itEnd; ++it)
	{
		clipAPoint(*it, BoundaryType::First, firstPointList, lastPointList, faceSeenList, outputArray);
	}

	clipLastPoint(firstPointList, lastPointList, faceSeenList, outputArray);

	return outputArray;
}

bool ArcWindow::polygonPipeline(Arc3DAttributedPointList& vertexList, Arc3DAttributedPoint* point, const bool endFlag)
{
	Arc3DPointH geom(point->position());
	ArcVector   vec(point->normalVector());
	const uint MAX_VERTEX_LIST_SIZE = 50U;

	// Run geometry through current transform
	geom = (*_pCurrentTransform) * geom;
	vec  = (*_pNormalTransform)  * vec;

	point->normalVector(vec);
	point->updateWorldPosition(geom);
	
	// Run through world to clip
	geom = ArcTransformMatrixH::world_to_camera(geom, _cameraEyePoint, _cameraAtPoint, _cameraUpVector);

	geom = ArcTransformMatrixH::camera_to_clip(geom, _cameraFov, _clippingNear, _clippingFar, static_cast<double>(_width) / static_cast<double>(_height));
	
	point->updatePosition(geom);

	// Store in vertex list
	if (vertexList.size() == MAX_VERTEX_LIST_SIZE)
	{
		return false; // Overflow
	}

	vertexList.push_back(point);

	if (endFlag == false) // Move along to the next vertex
	{
		return true;
	}
	
	// Put the surface normal to world coordinates.
	_surfaceNormal = (*_pNormalTransform) * _surfaceNormal;

	Arc3DAttributedPointList clipped_list = polygonClip(vertexList);

	if (clipped_list.size() > 0U)
	{
		// There's something left! --- Let's draw it
	
		// Pre process vertex list
		for (uint i = 0; i < clipped_list.size(); i++)
		{
			// Convert geometry to device coordinates
			Arc3DPointH dev(clipped_list[i]->position());

			dev = ArcTransformMatrixH::clip_to_device(dev, _width, _height);

			// Normalize and update.
			clipped_list[i]->updatePosition(dev.toCartesianPoint());

			// Normalize the rest of the points.
			clipped_list[i]->constant(     clipped_list[i]->constant()      / dev.w());
			clipped_list[i]->color(        clipped_list[i]->color()         / dev.w());
			clipped_list[i]->opacity(      clipped_list[i]->opacity()       / dev.w());
			clipped_list[i]->textureS(     clipped_list[i]->textureS()      / dev.w());
			clipped_list[i]->textureT(     clipped_list[i]->textureT()      / dev.w());
			clipped_list[i]->normalVector( clipped_list[i]->normalVector()  / dev.w());
			clipped_list[i]->weight(       clipped_list[i]->weight()        / dev.w());
			//clipped_list[i]->worldPosition(clipped_list[i]->worldPosition() / dev.w());
		}

		_edgeTable->scan_convert(clipped_list);
	}

	return true;
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

ArcColor ArcWindow::calcAmbient(const ArcColor& color)
{
	ArcWindow* pWindow = ArcWindow::window();

	// Calculating ambient values.
	const double redAmbientIntensity   = pWindow->_ambientCoefficient * pWindow->_surfaceColor.red()   * pWindow->_ambientLight->color.red();
	const double greenAmbientIntensity = pWindow->_ambientCoefficient * pWindow->_surfaceColor.green() * pWindow->_ambientLight->color.green();
	const double blueAmbientIntensity  = pWindow->_ambientCoefficient * pWindow->_surfaceColor.blue()  * pWindow->_ambientLight->color.blue();

	return ArcColor(redAmbientIntensity, greenAmbientIntensity, blueAmbientIntensity);
}

ArcColor ArcWindow::calcDiffuse(const ArcColor& color, const ArcVector& normalVector, const Arc3DPoint& position)
{
	ArcWindow* pWindow = ArcWindow::window();

	// Calculating diffuse values.
	//    Loop through lights and multiply by normal.
	double redDiffuseSum   = 0.0;
	double greenDiffuseSum = 0.0;
	double blueDiffuseSum  = 0.0;

	for (ArcFarLightList::iterator it = pWindow->_farLightList.begin(); it != pWindow->_farLightList.end(); ++it)
	{
		// Clamp all vectors between 0 and 1.
		double vecSum = ArcMath::clamp(normalVector.normalized().dot((*it)->vector.normalized()), 0.0, 1.0);
		redDiffuseSum   += vecSum * (*it)->color.red();
		greenDiffuseSum += vecSum * (*it)->color.green();
		blueDiffuseSum  += vecSum * (*it)->color.blue();
	}

	for (ArcPointLightList::iterator it = pWindow->_pointLightList.begin(); it != pWindow->_pointLightList.end(); ++it)
	{
		// Where does this vector go to? From the point light to the world xyz
		ArcVector pointVec(position, (*it)->point);

		const double value = 1.0 / pointVec.magnitudeSquared();

		double vecSum = ArcMath::clamp(normalVector.normalized().dot(pointVec.normalized()), 0.0, 1.0);
		redDiffuseSum   += vecSum * (*it)->color.red()   * value;
		greenDiffuseSum += vecSum * (*it)->color.green() * value;
		blueDiffuseSum  += vecSum * (*it)->color.blue()  * value;
	}

	const double redDiffuseIntensity   = pWindow->_diffuseCoefficient * pWindow->_surfaceColor.red()   * redDiffuseSum;
	const double greenDiffuseIntensity = pWindow->_diffuseCoefficient * pWindow->_surfaceColor.green() * greenDiffuseSum;
	const double blueDiffuseIntensity  = pWindow->_diffuseCoefficient * pWindow->_surfaceColor.blue()  * blueDiffuseSum;

	return ArcColor(redDiffuseIntensity, greenDiffuseIntensity, blueDiffuseIntensity);
}

ArcColor ArcWindow::calcSpecular(const ArcColor& color, const ArcVector& normalVector, const Arc3DPoint& position, const bool isMetal)
{
	ArcWindow* pWindow = ArcWindow::window();
	
	// Calculating specular values;
	double redSpecularSum   = 0.0;
	double greenSpecularSum = 0.0;
	double blueSpecularSum  = 0.0;

	const ArcVector camera = ArcVector(position, pWindow->cameraEyePoint());

	for (ArcFarLightList::iterator it = pWindow->_farLightList.begin(); it != pWindow->_farLightList.end(); ++it)
	{
		ArcVector vec = (*it)->vector;
		vec.reflect(normalVector);

		double vecSum = pow(ArcMath::clamp(camera.normalized().dot(vec.normalized()), 0.0, 1.0), pWindow->_specularExponent);
		redSpecularSum   += (*it)->color.red()   * vecSum;
		greenSpecularSum += (*it)->color.green() * vecSum;
		blueSpecularSum  += (*it)->color.blue()  * vecSum;
	}

	for (ArcPointLightList::iterator it = pWindow->_pointLightList.begin(); it != pWindow->_pointLightList.end(); ++it)
	{
		// Where does this vector go to? From the point light to the world xyz
		ArcVector pointVec(position, (*it)->point);

		const double value = 1.0 / pointVec.magnitudeSquared();

		ArcVector vec = pointVec;
		vec.reflect(normalVector);

		double vecSum = pow(ArcMath::clamp(camera.normalized().dot(vec.normalized()), 0.0, 1.0), pWindow->_specularExponent);
		redSpecularSum   += (*it)->color.red()   * vecSum * value;
		greenSpecularSum += (*it)->color.green() * vecSum * value;
		blueSpecularSum  += (*it)->color.blue()  * vecSum * value;
	}

	double redSpecularIntensity;
	double greenSpecularIntensity;
	double blueSpecularIntensity;

	if (isMetal)
	{
		redSpecularIntensity   = pWindow->_specularCoefficient * pWindow->_surfaceColor.red()   * redSpecularSum;
		greenSpecularIntensity = pWindow->_specularCoefficient * pWindow->_surfaceColor.green() * greenSpecularSum;
		blueSpecularIntensity  = pWindow->_specularCoefficient * pWindow->_surfaceColor.blue()  * blueSpecularSum;
	}
	else
	{
		redSpecularIntensity   = pWindow->_specularCoefficient * pWindow->_specularColor.red()   * redSpecularSum;
		greenSpecularIntensity = pWindow->_specularCoefficient * pWindow->_specularColor.green() * greenSpecularSum;
		blueSpecularIntensity  = pWindow->_specularCoefficient * pWindow->_specularColor.blue()  * blueSpecularSum;
	}

	
	return ArcColor(redSpecularIntensity, greenSpecularIntensity, blueSpecularIntensity);
}

void ArcWindow::matte(Arc3DAttributedPoint* pPoint)
{
	ArcWindow* pWindow = ArcWindow::window();
	ArcVector normalVector = pWindow->_surfaceNormal;
	ArcColor& colorMutable = pPoint->colorM();

	if (pWindow->_vertexNormalFlag && pWindow->_useInterpolationFlag)
	{
		normalVector = pPoint->normalVector();
	}

	const ArcColor ambientIntensity = calcAmbient(colorMutable);
	const ArcColor diffuseIntensity = calcDiffuse(colorMutable, normalVector, pPoint->worldPosition());

	// Sum all values (No specular for matte).
	const double   redIntensity = ambientIntensity.red()   + diffuseIntensity.red();
	const double greenIntensity = ambientIntensity.green() + diffuseIntensity.green();
	const double  blueIntensity = ambientIntensity.blue()  + diffuseIntensity.blue();

	colorMutable = ArcColor(ArcMath::clamp(redIntensity, 0.0, 1.0), ArcMath::clamp(greenIntensity, 0.0, 1.0), ArcMath::clamp(blueIntensity, 0.0, 1.0));
}

void ArcWindow::metal(Arc3DAttributedPoint* pPoint)
{
	ArcWindow* pWindow = ArcWindow::window();
	ArcVector normalVector = pWindow->_surfaceNormal;
	ArcColor& colorMutable = pPoint->colorM();

	if (ArcWindow::window()->_vertexNormalFlag && ArcWindow::window()->_useInterpolationFlag)
	{
		normalVector = pPoint->normalVector();
	}

	const ArcColor ambientIntensity  = calcAmbient(colorMutable);
	const ArcColor specularIntensity = calcSpecular(colorMutable, normalVector, pPoint->worldPosition(), true);

	// Sum all values (Don't do diffuse for metal).
	const double   redIntensity = ambientIntensity.red()   + specularIntensity.red();
	const double greenIntensity = ambientIntensity.green() + specularIntensity.green();
	const double  blueIntensity = ambientIntensity.blue()  + specularIntensity.blue();

	colorMutable = ArcColor(ArcMath::clamp(redIntensity, 0.0, 1.0), ArcMath::clamp(greenIntensity, 0.0, 1.0), ArcMath::clamp(blueIntensity, 0.0, 1.0));
}

void ArcWindow::plastic(Arc3DAttributedPoint* pPoint)
{
	ArcWindow* pWindow = ArcWindow::window();
	ArcVector normalVector = pWindow->_surfaceNormal;
	ArcColor& colorMutable = pPoint->colorM();

	if (ArcWindow::window()->_vertexNormalFlag && ArcWindow::window()->_useInterpolationFlag)
	{
		normalVector = pPoint->normalVector();
	}
	
	const ArcColor ambientIntensity  = calcAmbient(colorMutable);
	const ArcColor diffuseIntensity  = calcDiffuse(colorMutable, normalVector, pPoint->worldPosition());
	const ArcColor specularIntensity = calcSpecular(colorMutable, normalVector, pPoint->worldPosition(), false);

	// Sum all values
	const double   redIntensity = ambientIntensity.red()   + diffuseIntensity.red()   + specularIntensity.red();
	const double greenIntensity = ambientIntensity.green() + diffuseIntensity.green() + specularIntensity.green();
	const double  blueIntensity = ambientIntensity.blue()  + diffuseIntensity.blue()  + specularIntensity.blue();

	colorMutable = ArcColor(ArcMath::clamp(redIntensity, 0.0, 1.0), ArcMath::clamp(greenIntensity, 0.0, 1.0), ArcMath::clamp(blueIntensity, 0.0, 1.0));
}
