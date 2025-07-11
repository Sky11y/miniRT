#include "mini_rt.h"
#include "scene_elements.h"

t_vec3f	vt_mul(const t_vec3f v, float t)
{
	return ((t_vec3f){v.x * t, v.y * t, v.z * t});
}

t_vec3f	vt_div(const t_vec3f v, float t)
{
	if (fabs(t) < 1e-8)
		return ((t_vec3f){0, 0, 0});
	return ((t_vec3f){v.x / t, v.y / t, v.z / t});
}

t_vec3f	vv_add(const t_vec3f u, const t_vec3f v)
{
	return ((t_vec3f){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec3f	vv_sub(const t_vec3f u, const t_vec3f v)
{
	return ((t_vec3f){u.x - v.x, u.y - v.y, u.z - v.z});
}

t_vec3f	vv_mul(const t_vec3f v, const t_vec3f u)
{
	return ((t_vec3f){v.x * u.x, v.y * u.y, v.z * u.z});
}
