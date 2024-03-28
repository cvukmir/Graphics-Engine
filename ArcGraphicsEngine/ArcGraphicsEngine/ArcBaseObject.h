#pragma once

#ifndef ARCBASEOBJECT_H
#define ARCBASEOBJECT_H

// Stdlib
#include <string>

// ArcFramework
#include "ArcColor.h"

class ArcBaseObject
{
public: // Constructor/Destructor(s) //

	ArcBaseObject();

	~ArcBaseObject();


private: // Variables //

	ArcColor    _color;
	std::string _name;
};

#endif // !ARCBASEOBJECT_H