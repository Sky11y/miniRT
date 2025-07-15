#include "mini_rt.h"
#include "scene_elements.h"

inline static bool	hit_anything(const t_ray r, const t_hittables *htbl,
		const float max_t)
{
	t_hit_record	hr;
	float			closest_t;

	closest_t = max_t + 1.0f;
	if (htbl->sphere_count)
	{
		hit_all_spheres(r, &closest_t, htbl, &hr);
		if (closest_t < max_t)
			return (true);
	}
	if (htbl->cylinder_count)
	{
		hit_all_cylinders(r, &closest_t, htbl, &hr);
		if (closest_t < max_t)
			return (true);
		hit_all_cylinder_caps(r, &closest_t, htbl, &hr);
		if (closest_t < max_t)
			return (true);
	}
	if (htbl->plane_count)
	{
		hit_all_planes(r, &closest_t, htbl, &hr);
		if (closest_t < max_t)
		return (true);
	}
	return (false);
}

float	count_light(const t_vec3f normal, const t_vec3f hp,
		const t_lights *light, const t_hittables *htbl)
{
	float			intensity;
	t_vec3f			light_dir;
	float			diffuse;
	const t_vec3f	hp_to_light = vv_sub(light->point_center, hp);
	float			max_t;

	intensity = light->ambient_brightness;
	max_t = v_length(hp_to_light);
	light_dir = unit_vector(hp_to_light);
	if (hit_anything((t_ray){hp, light_dir}, htbl, max_t))
		return (intensity);
	diffuse = dot(normal, light_dir);
	if (diffuse > 0.0f)
		intensity += light->point_brightness * diffuse;
	return (intensity);
}
