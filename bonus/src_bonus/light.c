#include "mini_rt.h"
#include "scene_elements.h"

inline static bool	hit_anything(const t_ray r, const t_hittables *htbl)
{
	t_hit_record	hr;
	float			closest_t;

	closest_t = INFINITY;
	if (htbl->sphere_count)
	{
		hit_all_spheres(r, &closest_t, htbl, &hr);
		if (closest_t != INFINITY)
			return (true);
	}
	if (htbl->cylinder_count)
	{
		hit_all_cylinders(r, &closest_t, htbl, &hr);
		if (closest_t != INFINITY)
			return (true);
		hit_all_cylinder_caps(r, &closest_t, htbl, &hr);
		if (closest_t != INFINITY)
			return (true);
	}
	if (htbl->plane_count)
	{
		hit_all_planes(r, &closest_t, htbl, &hr);
		if (closest_t != INFINITY)
			return (true);
	}
	return (false);
}

float	count_light(const t_vec3f normal, const t_vec3f hp,
		const t_lights *light, const t_hittables *htbl)
{
	float			i;
	t_vec3f			light_dir;
	float			diffuse;

	i = light->ambient_brightness;
	light_dir = unit_vector(vv_sub(light->point_center, hp));
	if (hit_anything((t_ray){hp, light_dir}, htbl))
		return (i);
	diffuse = dot(normal, light_dir);
	if (diffuse > 0.0f)
		i += light->point_brightness * diffuse;
	return (i);
}
