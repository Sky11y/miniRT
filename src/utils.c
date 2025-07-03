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

t_vec3f vt_multiply(const t_vec3f v, float t)
{
	return (t_vec3f){v.x * t, v.y * t, v.z * t};
}

t_vec3f vt_division(const t_vec3f v, float t)
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

t_vec3f	vv_multiply(const t_vec3f v, const t_vec3f u)
{
	return (t_vec3f){v.x * u.x, v.y * u.y, v.z * u.z};
}

t_vec3f at(t_ray r, float t)
{
	return (t_vec3f)vv_add(r.origin, vt_multiply(r.direction, t));
}

t_vec3f random_v()
{
	return (t_vec3f){random_float(), random_float(), random_float()};
}


t_vec3f random_v_range(float min, float max)
{
	return (t_vec3f){ random_range(min, max),
					  random_range(min, max),
					  random_range(min, max) };
}

t_vec3f random_unit_vector()
{
	t_vec3f p;
	float lensq;

	while (true)
	{
		p = random_v_range(-1, 1);
		lensq = v_length_squared(p);
		if (lensq > 1e-8 && lensq <= 1.0)
			return (vt_division(p, sqrt(lensq)));
	}
}
/*This will most likely not be needed and can be removed
t_vec3f random_on_hemisphere(const t_vec3f normal)
{
	t_vec3f on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0)
		return (on_unit_sphere);
	return (rotate_v(on_unit_sphere));
}*/

float random_float( void )
{
	return (float)rand() / ((float)RAND_MAX + 1.0f);
}

float random_range(float min, float max)
{
	return min + (max - min) * random_float();
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

t_vec3f	reflect(const t_vec3f v, const t_vec3f n)
{
	t_vec3f tmp;

	tmp = vt_multiply(n, 2 * dot(v, n));
	return (vv_sub(v, tmp));
}

/*This function is not needed on the mandatory part
t_vec3f	get_material(t_material mat)
{
	if (mat == diffuse)
		return (t_vec3f){0.1, 0.2, 0.5};
	else if (mat == metallic)
		return (t_vec3f){0.8, 0.8, 0.8};
	return (t_vec3f){0, 0, 0};
}*/

bool	near_zero(const t_vec3f v)
{
	const float eps = 1e-8;
	return (fabsf(v.x) < eps && fabsf(v.y) < eps && fabsf(v.z) < eps);
}
