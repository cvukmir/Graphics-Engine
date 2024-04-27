#pragma once

#ifndef ARCPOINTLIGHT_HPP
#define ARCPOINTLIGHT_HPP

#include "ArcColor.h"
#include "Arc3DPoint.h"

struct ArcPointLight
{
public: // Constructor //

	ArcPointLight()
	{
	}

	ArcPointLight(const ArcColor& color, const Arc3DPoint& point)
	{
		this->color = color;
		this->point = point;
	}


public: // Variables //

	ArcColor   color;
	Arc3DPoint point;
};

#endif // !ARCPOINTLIGHT_HPP