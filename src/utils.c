#include "mini_rt.h"
#include "scene_elements.h"

float 	dot(const t_vec3f u, const t_vec3f v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3f	cross(const t_vec3f u, const t_vec3f v)
{
	return (t_vec3f){u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x};
}

t_vec3f rotate_v(const t_vec3f v)
{
	return (t_vec3f){-v.x, -v.y, -v.z};
}

t_vec3f	unit_vector(const t_vec3f v)
{
	const float length = v_length(v);
	if (length < 1e-8)
		return (t_vec3f){0, 0, 0};
	return (t_vec3f){v.x / length, v.y / length, v.z / length};
}

float v_length(const t_vec3f v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float v_length_squared(const t_vec3f v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3f vt_mul(const t_vec3f v, float t)
{
	return (t_vec3f){v.x * t, v.y * t, v.z * t};
}

t_vec3f vt_div(const t_vec3f v, float t)
{
	if (fabs(t) < 1e-8)
		return (t_vec3f){0, 0, 0};
	return (t_vec3f){v.x / t, v.y / t, v.z / t};
}

t_vec3f vv_add(const t_vec3f u, const t_vec3f v)
{
	return (t_vec3f){u.x + v.x, u.y + v.y, u.z + v.z};
}

t_vec3f vv_sub(const t_vec3f u, const t_vec3f v)
{
	return (t_vec3f){u.x - v.x, u.y - v.y, u.z - v.z};
}

t_vec3f	vv_mul(const t_vec3f v, const t_vec3f u)
{
	return (t_vec3f){v.x * u.x, v.y * u.y, v.z * u.z};
}

t_vec3f at(t_ray r, float t)
{
	return (t_vec3f)vv_add(r.origin, vt_mul(r.direction, t));
}

float clamp(const float x, const float min, const float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

float degrees_to_rad(float degrees)
{
	return degrees * (M_PI / 180.0);
}
