#include "mini_rt.h"

float	inverse_sqrt( float nbr)
{
	const float threehalfs = 1.5f;
	float		x2;
	float		y;
	long		i;

	x2 = nbr * 0.5f;
	y = nbr;
	i = *(long *)&y;
	i = 0x5f3759df - ( i >> 1 );
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}
