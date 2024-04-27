#pragma once

#ifndef ARCAMBIENTLIGHT_HPP
#define ARCAMBIENTLIGHT_HPP

#include "ArcColor.h"

struct ArcAmbientLight
{
public: // Constructor //

	ArcAmbientLight()
	{
	}

	ArcAmbientLight(const ArcColor& color)
	{
		this->color = color;
	}


public: // Variables //

	ArcColor color;
};

#endif // !ARCAMBIENTLIGHT_HPP