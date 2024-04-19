#include "ArcBaseAttributes.h"

ArcBaseAttributes::ArcBaseAttributes()
	: _opacity(0.0)
	, _s      (0.0)
	, _t      (0.0)
	, _weight (0.0)
{
}

ArcBaseAttributes::~ArcBaseAttributes()
{
}

void             ArcBaseAttributes::color(const ArcColor value)    { _color = value; }
const ArcColor&  ArcBaseAttributes::color() const                  { return _color;  }

void             ArcBaseAttributes::opacity(const double value)    { _opacity = value; }
const double     ArcBaseAttributes::opacity() const                { return _opacity;  }

void             ArcBaseAttributes::textureS(const double value)   { _s = value; }
const double     ArcBaseAttributes::textureS() const               { return _s;  }

void             ArcBaseAttributes::textureT(const double value)   { _t = value; }
const double     ArcBaseAttributes::textureT() const               { return _t;  }

void             ArcBaseAttributes::vector(const ArcVector& value) { _vector = value; }
const ArcVector& ArcBaseAttributes::vector() const                 { return _vector;  }

void             ArcBaseAttributes::weight(const double value)     { _weight = value; }
const double     ArcBaseAttributes::weight() const                 { return _weight;  }
