#include "mini_rt.h"
#include "scene_elements.h"

inline t_vec3f	vt_mul(const t_vec3f v, float t)
{
	return ((t_vec3f){v.x * t, v.y * t, v.z * t});
}

inline t_vec3f	vt_div(const t_vec3f v, float t)
{
	float	inverse;

	if (fabsf(t) < 1e-4f)
		return ((t_vec3f){0, 0, 0});
	inverse = 1.0f / t;
	return ((t_vec3f){v.x * inverse, v.y * inverse, v.z * inverse});
}

inline t_vec3f	vv_add(const t_vec3f u, const t_vec3f v)
{
	return ((t_vec3f){u.x + v.x, u.y + v.y, u.z + v.z});
}

inline t_vec3f	vv_sub(const t_vec3f u, const t_vec3f v)
{
	return ((t_vec3f){u.x - v.x, u.y - v.y, u.z - v.z});
}
