#pragma once

#ifndef ARCMATH_H
#define ARCMATH_H

class ArcMath
{
public: // Constructor/Destructor //

	ArcMath();

	~ArcMath();

public: // Methods - Static //

	static void  clamp(double& value, const double min, const double max);
	static double clamp(const double value, const double min, const double max);

};


#endif // !ARCMATH_H