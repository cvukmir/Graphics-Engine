#pragma once

#ifndef Arc2DPoint_H
#define Arc2DPoint_H

class Arc2DPoint
{
public:
	Arc2DPoint();
	Arc2DPoint(int x, int y);

	~Arc2DPoint();

public:

	void      x(const int value);
	const int x() const;

	void      y(const int value);
	const int y() const;

private:
	int _x;
	int _y;

};

#endif // !Arc2DPoint_H