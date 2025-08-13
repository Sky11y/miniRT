#include "mini_rt.h"
#include "scene_elements.h"

inline float	dot(const t_vec3f *u, const t_vec3f *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}

inline t_vec3f	cross(const t_vec3f u, const t_vec3f v)
{
	return ((t_vec3f){
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	});
}

inline t_vec3f	rotate_v(const t_vec3f v)
{
	return ((t_vec3f){-v.x, -v.y, -v.z});
}

inline t_vec3f	unit_vector(const t_vec3f v)
{
	const float	length = v_length(&v);
	float		inverse;

	if (length < 1e-2f)
		return ((t_vec3f){0, 0, 0});
	inverse = 1.0f / length;
	return ((t_vec3f){v.x * inverse, v.y * inverse, v.z * inverse});
}

inline t_vec3f	at(const t_ray *r, float t)
{
	return ((t_vec3f)vv_add(r->origin, vt_mul(r->direction, t)));
}
