#pragma once

#ifndef ARCMATH_H
#define ARCMATH_H

class ArcMath
{
public: // Constructor/Destructor //

	ArcMath();

	~ArcMath();

public: // Methods - Static //

	void  clamp(float& value, const float min, const float max);
	float clamp(const float value, const float min, const float max);

};


#endif // !ARCMATH_H