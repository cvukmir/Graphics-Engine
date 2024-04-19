#pragma once

#ifndef ARCBASEATTRIBUTES_H
#define ARCBASEATTRIBUTES_H

#include "ArcColor.h"
#include "ArcVector.h"

class ArcBaseAttributes
{
public:

	ArcBaseAttributes();

	~ArcBaseAttributes();

public: // Properties //

	void             color(const ArcColor value);
	const ArcColor&  color() const;

	void             opacity(const double value);
	const double     opacity() const;

	void             textureS(const double value);
	const double     textureS() const;

	void             textureT(const double value);
	const double     textureT() const;

	void             vector(const ArcVector& value);
	const ArcVector& vector() const;

	void             weight(const double value);
	const double     weight() const;


private:

	ArcColor  _color;
	double    _opacity;
	double    _s;
	double    _t;
	ArcVector _vector;
	double    _weight;
};


#endif // !ARCBASEATTRIBUTES_H