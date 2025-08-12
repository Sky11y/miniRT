#include "mini_rt.h"
#include "scene_elements.h"

t_vec3f	reflection(const t_ray *r, const t_thread *t,
		const t_hit_record *hr, uint8_t depth)
{
	t_ray	reflected_ray;
	t_vec3f	reflected_color;
	t_vec3f	return_color;

	reflected_ray.direction = unit_vector(reflect(r->direction, hr->normal));
	reflected_ray.origin = vv_add(hr->hitpoint, vt_mul(hr->normal, EPSILON));
	reflected_color = ray_color(&reflected_ray, t, depth - 1);
	return_color = vt_mul(reflected_color, hr->reflect);
	return (return_color);
}

t_vec3f	refraction(const t_ray *r, const t_thread *t,
		const t_hit_record *hr, uint8_t depth)
{
	t_ray	refracted_ray;
	t_vec3f	refracted_color;

	refracted_ray.direction = refract_dir(r->direction, hr->normal, hr->ior,
			hr->face);
	if (v_length(&refracted_ray.direction) <= 0.0f)
		return ((t_vec3f){0, 0, 0});
	refracted_ray.direction = unit_vector(refracted_ray.direction);
	refracted_ray.origin = vv_sub(hr->hitpoint, vt_mul(hr->normal, EPSILON));
	refracted_color = ray_color(&refracted_ray, t, depth - 1);
	return (refracted_color);
}

t_vec3f	reflect_and_refract(const t_ray *r, const t_thread *t,
		const t_hit_record *hr, uint8_t depth)
{
	t_vec3f	reflected_color;
	t_vec3f	refracted_color;
	t_vec3f	combined_color;
	t_vec3f	transparent_color;
	float	kr;

	refracted_color = (t_vec3f){0, 0, 0};
	kr = schlick_prob(r->direction, hr->normal, hr->ior);
	if (kr < 1.0f)
		refracted_color = refraction(r, t, hr, depth);
	reflected_color = reflection(r, t, hr, depth);
	combined_color = vv_add(vt_mul(reflected_color, kr),
			vt_mul(refracted_color, 1.0f - kr));
	transparent_color = vt_mul(combined_color, hr->transparency);
	return (transparent_color);
}
