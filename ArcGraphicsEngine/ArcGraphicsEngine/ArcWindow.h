#pragma once

#ifndef ARCWINDOWS_H
#define ARCWINDOWS_H

#include <Windows.h>

#include "Arc2DPoint.h"
#include "ArcColor.h"

class ArcWindow
{
private: // Singleton

	ArcWindow();


public:

	~ArcWindow();


public: // Static methods

	static ArcWindow* window();


public: // Properties

	void          memory(UINT32* value);
	const UINT32* memory() const;

	void      windowHeight(const int value);
	const int windowHeight() const;

	void      windowWidth(const int value);
	const int windowWidth() const;

	void       isRunning(const bool value);
	const bool isRunning() const;

	void      frameNumber(const int value);
	const int frameNumber() const;

	void           currentColor(const ArcColor value);
	const ArcColor currentColor() const;

public: // Methods

	// Delete copy constructor
	ArcWindow(const ArcWindow& obj) = delete;

	void initializeMemory();

	void fillBackground(const ArcColor color);
	void drawPoint(const Arc2DPoint point);
	void drawLine(const Arc2DPoint startPoint, const Arc2DPoint endPoint);
	void drawCircle(const Arc2DPoint startPoint, int radius);
	void fill(const Arc2DPoint startPoint);

private: // Methods

	ArcColor colorAt(const int xPos, const int yPos);

	void fillSpan(const int startX, const int endX, const int y);

	bool findspan(int& startX, int& endX, const int y);

	void fff4(const int startX, const int endX, const int y);

	void drawPixel(const int xPos, const int yPos);

	bool inWindow(const int xPos, const int yPos);


private: // Static variables

	static ArcWindow* _pInstancePtr;


private:

	int      _height;
	UINT32*  _pMemory;
	int      _width;
	bool     _isRunning;
	int      _frameNumber;
	ArcColor _currentColor;
};

#endif // !ARCWINDOWS_H