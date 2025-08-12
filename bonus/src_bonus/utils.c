#include "mini_rt.h"
#include "scene_elements.h"

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

t_vec3f	reflect(const t_vec3f v, const t_vec3f n)
{
	t_vec3f	tmp;

	tmp = vt_mul(n, 2 * dot(&v, &n));
	return (vv_sub(v, tmp));
}

//etas[0] = etai, etas[1] = etat, etas[2] = eta
t_vec3f	refract_dir(const t_vec3f v, const t_vec3f n, const float ior,
		const int front_face)
{
	float	cosi;
	float	etas[3];
	float	k;
	float	temp;
	t_vec3f	normal;

	normal = n;
	cosi = clamp(dot(&n, &v), -1.0f, 1.0f);
	etas[0] = 1.0f;
	etas[1] = ior;
	if (front_face == -1)
	{
		cosi = -cosi;
		temp = etas[0];
		etas[0] = etas[1];
		etas[1] = temp;
		normal = rotate_v(normal);
	}
	etas[2] = etas[0] / etas[1];
	k = 1 - etas[2] * etas[2] * (1 - cosi * cosi);
	if (k < 0.0)
		return ((t_vec3f){0, 0, 0});
	return (vv_add(vt_mul(v, etas[2]), vt_mul(n, etas[2] * cosi - sqrt(k))));
}

// values[0] = cosi, values[1] = etai, values[2] = etat
inline float	schlick_prob(const t_vec3f v, const t_vec3f n, const float ior)
{
	float	r0;
	float	cosi;
	float	etai;
	float	etat;
	float	temp;

	cosi = clamp(dot(&v, &n), -1.0f, 1.0f);
	etai = 1.0f;
	etat = ior;
	if (cosi > 0.0f)
	{
		temp = etai;
		etai = etat;
		etat = temp;
	}
	r0 = (etai - etat) / (etai + etat);
	r0 = r0 * r0;
	return (r0 + (1.0f - r0) * powf(1.0f - fabsf(cosi), 5.0f));
}
