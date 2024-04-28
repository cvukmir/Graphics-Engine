
#include "ArcMath.h"

ArcMath::ArcMath()
{
}

ArcMath::~ArcMath()
{
}

void ArcMath::clamp(float& value, const float min, const float max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}
}

float ArcMath::clamp(const float value, const float min, const float max)
{
	if (value < min)
	{
		return min;
	}
	else if (value > max)
	{
		return max;
	}
}
