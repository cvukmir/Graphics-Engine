#pragma once

#ifndef ARCWINDOWS_H
#define ARCWINDOWS_H

// Windows
#include <Windows.h>

#include <string>


#include "Arc2DPoint.h"
#include "Arc3DPoint.h"
#include "Arc3DPointH.h"
#include "ArcVector.h"
#include "ArcColor.h"
#include "ArcTypedefs.h"
#include "ArcTransformMatrixH.h"
#include "Arc3DLine.h"
#include "ArcEdgeTable.h"
#include "ArcAmbientLight.hpp"
#include "ArcFarLight.hpp"
#include "ArcPointLight.hpp"

#include "ArcEnums.h"

class ArcWindow
{
private: // Singleton Constructor //

	ArcWindow();


public: // Destructor //

	~ArcWindow();


public: // Static Methods (Singleton) //

	// Creates the one and only instance of this object.
	static ArcWindow* window();


public: // Variables - Shading //
	
	void (*_pSurfaceShader)(Arc3DAttributedPoint*);


public: // Properties //

	void                         ambientCoefficient(double value);        // Sets the ambient coefficient.
	const double                 ambientCoefficient() const;              // Gets the ambient coefficient.

	ArcAmbientLight*             ambientLight() const;                    // Gets the ambient light of the scene.

	void                         backgroundColor(const ArcColor& color);  // Sets the default background color for new frames.

	void                         cameraAt(const Arc3DPoint& value);       // Sets the camera look point.
	const Arc3DPoint&            cameraAt() const;                        // Gets the camera look point.

	void                         cameraEyePoint(const Arc3DPoint& value); // Sets the camera position.
	const Arc3DPoint&            cameraEyePoint() const;                  // Gets the camera position.

	void                         cameraFov(const double value);           // Sets the camera FOV (degrees).
	const double                 cameraFov() const;                       // Gets the camera FOV (degrees).

	void                         cameraUpVector(const ArcVector& value);  // Sets the camera up vector.
	const ArcVector&             cameraUpVector() const;                  // Gets the camera up vector.

	void                         clippingFar(const double value);         // Sets the far clipping plane distance.
	const double                 clippingFar() const;                     // Gets the far clipping plane distance.

	void                         clippingNear(const double value);        // Sets the near clipping plane distance.
	const double                 clippingNear() const;                    // Gets the near clipping plane distance.

	void                         currentColor(const ArcColor value);      // Sets the current drawing color.
	const ArcColor               currentColor() const;                    // Gets the current drawing color.

	void                         diffuseCoefficient(double value);        // Sets the diffuse coefficient.
	const double                 diffuseCoefficient() const;              // Gets the diffuse coefficient.

	ArcFarLightList&             farLightList();                          // Gets the far light list.

	void                         frameNumber(const int value);            // Sets the current frame number.
	const int                    frameNumber() const;                     // Gets the current frame number.

	ArcFrameList::const_iterator frameBegin() const;                      // Gets the first frame of the frame list.
	ArcFrameList::const_iterator frameEnd()  const;                       // Gets the last  frame of the frame last.

	void                         isRunning(const bool value);             // Sets whether the display window is running.
	const bool                   isRunning() const;                       // Gets whether the display window is running.

	const UINT32*                memory() const;                          // Gets the current memory color map.

	ArcPointLightList&           pointLightList();                        // Gets the point light list.

	void                         specularCoefficient(double value);       // Sets the diffuse coefficient.
	const double                 specularCoefficient() const;             // Gets the diffuse coefficient.

	void                         specularColor(const ArcColor value);     // Sets the specular color.
	const ArcColor               specularColor() const;                   // Gets the specular color.

	void                         specularExponent(double value);          // Sets the diffuse exponent.
	const double                 specularExponent() const;                // Gets the diffuse exponent.

	void                         surfaceColor(const ArcColor value);      // Sets the surface drawing color.
	const ArcColor               surfaceColor() const;                    // Gets the surface drawing color.

	void                         useInterpolation(const bool value);      // Sets the surface drawing color.
	const bool                   useInterpolation() const;                // Gets the surface drawing color.

	void  vertexNormalFlag(const bool value);

	void                         windowHeight(const int value);           // Sets the height of the display window.
	const int                    windowHeight() const;                    // Gets the height of the display window.

	void                         windowWidth(const int value);            // Sets the width of the display window.
	const int                    windowWidth() const;                     // Gets the width of the display window.


public: // Methods //

	/* Delete copy constructor */
	ArcWindow(const ArcWindow& value) = delete;

	/* Clears the current transformation matrix back to the identity matrix. */
	void clearTransformationMaxtrix();

	/* Draws a circle at the given start point with the given radius using the currently set color. */
	void draw2DCircle(const Arc3DPoint& startPoint, const int radius);

	/* Draws a pixel in memory at the given position using the currently set color. */
	void draw2DPixel(const int xPos, const int yPos);

	/* Draws a 3D Pixel in memory at the given position using the currently set color. */
	void draw3DPixel(const Arc3DPoint& point);


	void draw3DPixel(const Arc3DPoint& point, const ArcColor& color);

	/* Draws the given line with the currently set color (Bresenham's Line Drawing Algorithm). */
	void draw2DLine(const Arc2DPoint& startPoint, const Arc2DPoint& endPoint);

	/* Draws the given point with the currently set color. */
	void draw2DPoint(const Arc2DPoint& point);

	/* Draws a 3D circle on the given plane with the given radius. */
	void draw3DCircle(const double radius, const double zMin, const double zMax, const double degrees, PlaneType plane);

	/* Draws the given 3D line onto the screen. */
	void draw3DLine(const Arc3DLine& line);

	/* Draws the given line between the two points (Sutherland–Hodgman Clipping Algorithm). */
	void draw3DLine(const Arc3DPointH& startPoint, const Arc3DPointH& endPoint);

	/* Draws the given 3D point onto the screen. */
	void draw3DPoint(const Arc3DPoint& point);

	/* Run a cone through the pipeline.The cone should have a circular base of a given radius on the xy plane.The cone should have a given height in the positive z direction. */
	void drawCone(const double height, const double radius, const double degrees);

	/* Run the faces of the cube (+/- 1 in x, y, and z) through the transformation pipeline. */
	void drawCube();

	/* Run a circular cylinder through the pipeline.The ends should be circles of a given radius parallel to the xy plane.The circles are centered at(0, 0, zmin) and (0, 0, zmax) where zmin and zmax are the z coordinates of the ends of the cylinder.Thus the cylinder extends from - radius to radius in x and y and from zmin to zmax in z. */
	void drawCylinder(const double radius, const double zmin, const double zmax, const double degrees);

	/* Run a circular disc through the pipeline.The disk should have a given radius.The disk is parallel to the xy plane and centered about the z axis.A height parameters gives the position of the disk along the z axis. */
	void drawDisk(const double height, const double radius, const double thetaMax);

	bool drawPolygon(const Arc3DAttributedPointList& pointList);

	void drawHaloRing(double radius, double degrees, double width, double thickness);

	/* Run a sphere(or some representation of a sphere) through the pipeline.The sphere should be centered at the origin and have a radius given by a parameter. */
	void drawSphere(double radius, double zMin, double zMax, double degrees);

	/* Draws a sphere using the polygon sphere drawing technique. */
	void drawSphere2(double radius, double zMin, double zMax, double degrees);

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

	/* Rotates the current transformation matrix by the given rotation in the XY plane. */
	void rotateTransformationXY(const double degrees);

	/* Rotates the current transformation matrix by the given rotation in the YZ plane. */
	void rotateTransformationYZ(const double degrees);

	/* Rotates the current transformation matrix by the given rotation in the ZY plane. */
	void rotateTransformationZX(const double degrees);

	/* Scales the current transformation matrix by the given values. */
	void scaleTransformation(const double s1, const double s2, const double s3);

	void setMaterialType(const std::string& type);

	/* Translates the current transformation matrix by the given values. */
	void translateTransformation(const double t1, const double t2, const double t3);


private: // Methods //

	void clipAPoint(Arc3DAttributedPoint* pPoint, BoundaryType boundary, Arc3DAttributedPointList& firstPointList, Arc3DAttributedPointList& lastPointList, bool faceSeenList[6], Arc3DAttributedPointList& outputArray);

	void clipLastPoint(Arc3DAttributedPointList& firstPointList, Arc3DAttributedPointList& lastPointList, bool faceSeenList[6], Arc3DAttributedPointList& outputArray);

	/* Gets the color at the given position. */
	ArcColor colorAt(const int xPos, const int yPos);

	bool cross(Arc3DAttributedPoint* pPoint1, Arc3DAttributedPoint* pPoint2, BoundaryType boundary);

	void cyberPunk(double radius);

	/* Draws a point using the Digital Differential Analyzer algorithm. */
	void DDA(const Arc3DPoint& startPoint, const Arc3DPoint& endPoint);

	/* Recursive call to fill a given area. */
	void fastFloodFill(const int startX, const int endX, const int y, ArcColor seedColor);

	/* Fills the given span using the currently set color. */
	void fillSpan(const int startX, const int endX, const int y);

	/* Finds the span at the given start point and color to fill. */
	bool findspan(int& startX, int& endX, const int y, ArcColor seedColor);

	/* Gets the specified bit. */
	const uint getBit(const uint value, const uint place);

	Arc3DAttributedPoint* intersect(Arc3DAttributedPoint* pPoint1, Arc3DAttributedPoint* pPoint2, BoundaryType boundary);

	bool inside(Arc3DAttributedPoint* pPoint, BoundaryType boundary);

	/* Whether the given position is within the window bounds. */
	bool inWindow(const int xPos, const int yPos) const;

	/* Moves the current drawing point to the given point and draws a line between the previous point if flagged. */
	void linePipeline(const Arc3DPoint& point, const bool isDrawing);

	Arc3DAttributedPointList polygonClip(Arc3DAttributedPointList& pointList);

	/* Draws the given polygon to the screen. */
	bool polygonPipeline(Arc3DAttributedPointList& vertexList, Arc3DAttributedPoint* point, const bool endFlag);

	/* Draws the given point to the screen. */
	void pointPipeline(const Arc3DPoint& point);

private: // Static Variables //

	static ArcWindow* _pInstancePtr; // The only and only instance of this object.


private: // Static Methods //

	static ArcColor calcAmbient(const ArcColor& color);

	static ArcColor calcDiffuse(const ArcColor& color, const ArcVector& normalVector, const Arc3DPoint& position);

	static ArcColor calcSpecular(const ArcColor& color, const ArcVector& normalVector, const Arc3DPoint& position, const bool isMetal = false);


	static void matte(Arc3DAttributedPoint* pPoint);

	static void metal(Arc3DAttributedPoint* pPoint);

	static void plastic(Arc3DAttributedPoint* pPoint);


private: // Variables //

	ArcColor  _specularColor;
	double    _specularExponent;
	bool      _vertexColorFlag;
	bool      _vertexNormalFlag;
	bool      _vertexTextureFlag;
	bool      _useInterpolationFlag;
	ArcVector _viewingVector;
	ArcVector _surfaceNormal;
	ArcTransformationStack _normalTransformationStack; // The stack of transformations to perform on objects.


	double                 _ambientCoefficient;  // The ambient coefficient for lighting calculations.
	ArcAmbientLight*       _ambientLight;        // The ambient light of this scene.
	ArcColor               _backgroundColor;     // The background color to initialize each frame to.
	Arc3DPoint             _cameraAtPoint;       // The position of where the camera is looking at.
	Arc3DPoint             _cameraEyePoint;      // The position of the camera.
	double                 _cameraFov;           // The FOV of the camera (in degrees).
	ArcVector              _cameraUpVector;      // The "up" vector of the camera.
	double                 _clippingFar;         // The far clipping value.
	double                 _clippingNear;        // The near clipping value.
	ArcColor               _currentColor;        // The current drawing color.
	double                 _diffuseCoefficient;  // The diffuse coefficient for lighting calculations.
	ArcEdgeTable*          _edgeTable;           // Contains the edge table for scan conversion.
	ArcFarLightList        _farLightList;        // The list of far lights.
	ArcFrameList           _frameList;           // Contains all the frames to display to the window.
	int                    _frameNumber;         // The frame number of this window.
	int                    _height;              // The height of this window.
	bool                   _isRunning;           // Whether this window is currently running.
	ArcTransformMatrixH*   _pCurrentTransform;   // The current transformation matrix.
	double*                _pDepthBuffer;        // The current frame being changed.
	UINT32*                _pMemory;             // The current frame being changed.
	ArcTransformMatrixH*   _pNormalTransform;    // The current transformation matrix used for vector normals.
	Arc3DPointH            _prevClipPoint;       // Previously moved to point for drawing lines.
	ArcPointLightList      _pointLightList;      // The list of point lists.
	double                 _specularCoefficient; // The specular coefficient for lighting calculations.
	ArcColor               _surfaceColor;        // The color of the surface.
	ArcTransformationStack _transformationStack; // The stack of transformations to perform on objects.
	int                    _width;               // The width of this window.
};

#endif // !ARCWINDOWS_H