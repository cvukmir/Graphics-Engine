#pragma once

#ifndef ARCFARLIGHT_HPP
#define ARCFARLIGHT_HPP

#include "ArcColor.h"
#include "ArcVector.h"

struct ArcFarLight
{
public: // Constructor //

	ArcFarLight()
	{
	}

	ArcFarLight(const ArcColor& color, const ArcVector& vector)
	{
		this->color  = color;
		this->vector = vector;
	}


public: // Variables //

	ArcColor  color;
	ArcVector vector;
};


#endif // !ARCFARLIGHT_HPP