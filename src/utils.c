#include "mini_rt.h"

float	clamp(const float x, const float min, const float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

float	degrees_to_rad(float degrees)
{
	return (degrees * (M_PI / 180.0));
}
