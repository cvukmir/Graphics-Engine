#pragma once

#ifndef ARCWINDOWS_H
#define ARCWINDOWS_H

// Windows
#include <Windows.h>


#include "Arc2DPoint.h"
#include "Arc3DPoint.h"
#include "Arc3DPointH.h"
#include "ArcVector.h"
#include "ArcColor.h"
#include "ArcTypedefs.h"
#include "ArcTransformMatrixH.h"
#include "Arc3DLine.h"

class ArcWindow
{
private: // Singleton Constructor //

	ArcWindow();


public: // Destructor //

	~ArcWindow();


public: // Static Methods (Singleton) //

	// Creates the one and only instance of this object.
	static ArcWindow* window();


public: // Properties //

	void                         backgroundColor(const ArcColor& color);

	void                         cameraAt(const Arc3DPoint& value);
	const Arc3DPoint&            cameraAt() const;

	void                         cameraEyePoint(const Arc3DPoint& value);
	const Arc3DPoint&            cameraEyePoint() const;

	void                         cameraFov(const double value);
	const double                 cameraFov() const;

	void                         cameraUpVector(const ArcVector& value);
	const ArcVector&             cameraUpVector() const;

	void                         clippingFar(const double value);
	const double                 clippingFar() const;

	void                         clippingNear(const double value);
	const double                 clippingNear() const;

	void                         currentColor(const ArcColor value);                       // Sets the current drawing color.
	const ArcColor               currentColor() const;                                     // Gets the current drawing color.

	void                         frameNumber(const int value);                             // Sets the current frame number.
	const int                    frameNumber() const;                                      // Gets the current frame number.

	ArcFrameList::const_iterator frameBegin() const;                                      // Gets the first frame of the frame list.
	ArcFrameList::const_iterator frameEnd()  const;                                       // Gets the last  frame of the frame last.

	void                         isRunning(const bool value);                              // Sets whether the display window is running.
	const bool                   isRunning() const;                                        // Gets whether the display window is running.

	const UINT32*                memory() const;                                           // The current memory color map.

	void                         windowHeight(const int value);                            // Sets the height of the display window.
	const int                    windowHeight() const;                                     // Gets the height of the display window.

	void                         windowWidth(const int value);                             // Sets the width of the display window.
	const int                    windowWidth() const;                                      // Gets the width of the display window.


public: // Methods //

	/* Delete copy constructor */
	ArcWindow(const ArcWindow& value) = delete;

	/* Clears the current transformation matrix back to the identity matrix. */
	void clearTransformationMaxtrix();

	/* Draws a circle at the given start point with the given radius using the currently set color. */
	void draw2DCircle(const Arc3DPoint& startPoint, const int radius);

	// Draws a 3D circle on the given plane with the given radius.
	void draw3DCircle(const double radius, const double zMin, const double zMax, const double degrees, const PlaneTypes plane = PlaneTypes::XY);

	/* Run a cone through the pipeline.The cone should have a circular base of a given radius on the xy plane.The cone should have a given height in the positive z direction. */
	void drawCone(const double height, const double radius, const double degrees);

	/* Run the faces of the cube (+/- 1 in x, y, and z) through the transformation pipeline. */
	void drawCube();

	/* Run a circular cylinder through the pipeline.The ends should be circles of a given radius parallel to the xy plane.The circles are centered at(0, 0, zmin) and (0, 0, zmax) where zmin and zmax are the z coordinates of the ends of the cylinder.Thus the cylinder extends from - radius to radius in x and y and from zmin to zmax in z. */
	void drawCylinder(const double radius, const double zmin, const double zmax, const double degrees);

	/* Run a circular disc through the pipeline.The disk should have a given radius.The disk is parallel to the xy plane and centered about the z axis.A height parameters gives the position of the disk along the z axis. */
	void drawDisk(const double height, const double radius, const double thetaMax);

	/* Draws the given line with the currently set color. */
	void draw2DLine(const Arc2DPoint& startPoint, const Arc2DPoint& endPoint);

	/* Draws the given 3D line onto the screen. */
	void draw3DLine(const Arc3DLine& line);

	/* Draws the given point with the currently set color. */
	void draw2DPoint(const Arc2DPoint& point);

	/* Draws the given 3D point onto the screen. */
	void draw3DPoint(const Arc3DPoint& point);

	/* Run a sphere(or some representation of a sphere) through the pipeline.The sphere should be centered at the origin and have a radius given by a parameter. */
	void drawSphere(double radius, double zMin, double zMax, double degrees);

	/* Fills the area at the given start point with the currently set color. */
	void fill(const Arc2DPoint& startPoint);

	/* Fills the background with the given color. */
	void fillBackground(const ArcColor& color);

	/* Initialize the memory of the display to the width / height with a default color. */
	void initializeNewFrame();

	/* Pops a transformation off the transformation stack(does not return value). */
	void popTransformation();

	/* Pushes a transformation onto the transformation stack. */
	void pushTransformation();

	/* Translates the current transformation matrix by the given values. */
	void translateTransformation(const double t1, const double t2, const double t3);

	/* Scales the current transformation matrix by the given values. */
	void scaleTransformation(const double s1, const double s2, const double s3);

	/* Rotates the current transformation matrix by the given rotation in the XY plane. */
	void rotateTransformationXY(const double degrees);

	/* Rotates the current transformation matrix by the given rotation in the YZ plane. */
	void rotateTransformationYZ(const double degrees);

	/* Rotates the current transformation matrix by the given rotation in the ZY plane. */
	void rotateTransformationZX(const double degrees);




private: // Methods //

	/* Gets the color at the given position. */
	ArcColor colorAt(const int xPos, const int yPos);

	/* Draws a pixel in memory at the given position using the currently set color. */
	void drawPixel(const int xPos, const int yPos);

	/* Recursive call to fill a given area. */
	void fastFloodFill(const int startX, const int endX, const int y, ArcColor seedColor);

	/* Fills the given span using the currently set color. */
	void fillSpan(const int startX, const int endX, const int y);

	/* Finds the span at the given start point and color to fill. */
	bool findspan(int& startX, int& endX, const int y, ArcColor seedColor);

	/* Whether the given position is within the window bounds. */
	bool inWindow(const int xPos, const int yPos) const;

	/* Moves the current drawing point to the given point and draws a line between the previous point if flagged. */
	void linePipeline(const Arc3DPoint& point, const bool isDrawing);

	/* Draws the given point to the screen. */
	void pointPipeline(const Arc3DPoint& point);


private: // Static Variables //

	static ArcWindow* _pInstancePtr; // The only and only instance of this object.


private: // Variables //

	ArcColor               _backgroundColor;     // The background color to initialize each frame to.
	Arc3DPoint             _cameraAtPoint;       // The position of where the camera is looking at.
	Arc3DPoint             _cameraEyePoint;      // The position of the camera.
	double                 _cameraFov;           // The FOV of the camera (in degrees).
	ArcVector              _cameraUpVector;      // The "up" vector of the camera.
	double                 _clippingFar;         // The far clipping value.
	double                 _clippingNear;        // The near clipping value.
	ArcColor               _currentColor;        // The current drawing color.
	ArcFrameList           _frameList;           // Contains all the frames to display to the window.
	int                    _frameNumber;         // The frame number of this window.
	int                    _height;              // The height of this window.
	bool                   _isRunning;           // Whether this window is currently running.
	ArcTransformMatrixH*   _pCurrentTransform;   // The current transformation matrix.
	UINT32*                _pMemory;             // The current frame being changed.
	Arc3DPoint             _prevClipPoint;       // Previously moved to point for drawing lines.
	ArcTransformationStack _transformationStack; // The stack of transformations to perform on objects.
	int                    _width;               // The width of this window.
};

#endif // !ARCWINDOWS_H