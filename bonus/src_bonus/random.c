#include "mini_rt.h"

float	random_float(void)
{
	return ((float)rand() / ((float)RAND_MAX + 1.0f));
}

float	random_range(float min, float max)
{
	return (min + (max - min) * random_float());
}

t_vec3f	random_v(void)
{
	return ((t_vec3f){random_float(), random_float(), random_float()});
}

t_vec3f	random_v_range(float min, float max)
{
	return ((t_vec3f){
			random_range(min, max),
			random_range(min, max),
			random_range(min, max),
			});
}

t_vec3f	random_unit_vector(void)
{
	t_vec3f	p;
	float	lensq;

	while (true)
	{
		p = random_v_range(-1, 1);
		lensq = v_length_squared(p);
		if (lensq > 1e-8 && lensq <= 1)
			return (vt_div(p, sqrtf(lensq)));
	}
}
