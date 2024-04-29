
#include "ArcMath.h"

ArcMath::ArcMath()
{
}

ArcMath::~ArcMath()
{
}

void ArcMath::clamp(double& value, const double min, const double max)
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

double ArcMath::clamp(const double value, const double min, const double max)
{
	if (value < min)
	{
		return min;
	}
	else if (value > max)
	{
		return max;
	}

	return value;
}
