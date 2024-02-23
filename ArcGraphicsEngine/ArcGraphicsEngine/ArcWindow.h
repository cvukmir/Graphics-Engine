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

	void drawPixel(const int xPos, const int yPos, const ArcColor color);

	void          memory(UINT32* value);
	const UINT32* memory() const;

	void      windowHeight(const int value);
	const int windowHeight() const;

	void      windowWidth(const int value);
	const int windowWidth() const;

public: // Methods

	// Delete copy constructor
	ArcWindow(const ArcWindow& obj) = delete;

	void initializeMemory();

	void drawLine(const Arc2DPoint startPoint, const Arc2DPoint endPoint, const ArcColor color);
	void drawCircle(const Arc2DPoint startPoint, int radius, const ArcColor color);
	bool findspan(int& startX, int& endX, const int y, const ArcColor seedColor);
	void fff4(const int startX, const int endX, const int y, ArcColor seedColor);


private: // Methods

	bool inWindow(const int xPos, const int yPos);


private: // Static variables

	static ArcWindow* _pInstancePtr;


private:

	int     _height;
	UINT32* _pMemory;
	int     _width;

};

#endif // !ARCWINDOWS_H