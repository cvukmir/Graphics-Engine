#pragma once

#ifndef ARCWINDOWS_H
#define ARCWINDOWS_H

#include <Windows.h>

#include "Arc2DPoint.h"
#include "ArcColor.h"

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

	void           currentColor(const ArcColor value); // Sets the current drawing color.
	const ArcColor currentColor() const;               // Gets the current drawing color.

	void           frameNumber(const int value);       // Sets the current frame number.
	const int      frameNumber() const;                // Gets the current frame number.

	void           isRunning(const bool value);        // Sets whether the display window is running.
	const bool     isRunning() const;                  // Gets whether the display window is running.

	const UINT32*  memory() const;                     // The current memory color map.

	void           windowHeight(const int value);      // Sets the height of the display window.
	const int      windowHeight() const;               // Gets the height of the display window.

	void           windowWidth(const int value);       // Sets the width of the display window.
	const int      windowWidth() const;                // Gets the width of the display window.


public: // Methods //

	// Delete copy constructor
	ArcWindow(const ArcWindow& value) = delete;

	// Draws a circle at the given start point with the given radius using the currently set color.
	void drawCircle(const Arc2DPoint startPoint, int radius);

	// Draws the given line with the currently set color.
	void drawLine(const Arc2DPoint startPoint, const Arc2DPoint endPoint);

	// Draws the given point with the currently set color.
	void drawPoint(const Arc2DPoint point);

	// Fills the area at the given start point with the currently set color.
	void fill(const Arc2DPoint startPoint);

	// Fills the background with the given color.
	void fillBackground(const ArcColor color);

	// Initialize the memory of the display to the width/height with a default color.
	void initializeMemory();


private: // Methods //

	// Gets the color at the given position.
	ArcColor colorAt(const int xPos, const int yPos);

	// Draws a pixel in memory at the given position using the currently set color.
	void drawPixel(const int xPos, const int yPos);

	// Recursive call to fill a given area.
	void fastFloodFill(const int startX, const int endX, const int y, ArcColor seedColor);

	// Fills the given span using the currently set color.
	void fillSpan(const int startX, const int endX, const int y);

	// Finds the span at the given start point and color to fill.
	bool findspan(int& startX, int& endX, const int y, ArcColor seedColor);

	// Whether the given position is within the window bounds.
	bool inWindow(const int xPos, const int yPos);


private: // Static Variables //

	static ArcWindow* _pInstancePtr; // The only and only instance of this object.


private: // Variables //

	ArcColor _currentColor; // The current drawing color.
	int      _frameNumber;  // The frame number of this window.
	int      _height;       // The height of this window.
	bool     _isRunning;    // Whether this window is currently running.
	UINT32*  _pMemory;      // The color memory of this window.
	int      _width;        // The width of this window.
};

#endif // !ARCWINDOWS_H