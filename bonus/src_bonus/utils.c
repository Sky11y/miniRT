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

float	inverse_square_root(float nbr)
{
	const float	threehalfs = 1.5f;
	float		x2;
	float		y;
	long		i;

	x2 = nbr * 0.5f;
	y = nbr;
	memcpy(&i, &y, sizeof(float));
	i = 0x5f3759df - (i >> 1);
	memcpy(&y, &i, sizeof(float));
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}

bool	near_zero(const t_vec3f v)
{
	return (fabsf(v.x) < 1e-8 && fabsf(v.y) < 1e-8 && fabsf(v.z) < 1e-8);
}
