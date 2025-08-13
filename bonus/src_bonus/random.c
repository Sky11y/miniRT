/*#include "mini_rt.h"

inline float	random_float(void)
{
	return ((float)rand() / ((float)RAND_MAX + 1.0f));
}

inline float	random_range(float min, float max)
{
	return (min + (max - min) * random_float());
}

inline t_vec3f	random_v(void)
{
	return ((t_vec3f){random_float(), random_float(), random_float()});
}

inline t_vec3f	random_v_range(float min, float max)
{
	return ((t_vec3f){
		random_range(min, max),
		random_range(min, max),
		random_range(min, max),
	});
}

inline t_vec3f	random_unit_vector(void)
{
	t_vec3f	p;
	float	lensq;

	while (true)
	{
		p = random_v_range(-1.0f, 1.0f);
		lensq = v_length_squared(&p);
		if (lensq > 1e-8f && lensq <= 1.0f)
			return (vt_div(p, sqrtf(lensq)));
	}
}*/
