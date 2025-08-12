#include "mini_rt.h"
#include "scene_elements.h"

inline static bool	shadow_sphere(const t_ray *r, const t_hittables *htbl,
		const float max_t)
{
	t_hit_record	hr;
	float			closest_t;
	t_sphere		*hit;

	closest_t = max_t + 1.0f;
	hit_all_spheres(r, &closest_t, htbl, &hr);
	if (closest_t > max_t)
		return (false);
	hit = htbl->spheres + hr.index;
	if (hit->mat.transparency > 0.5f)
		return (false);
	return (true);
}

inline static bool	shadow_cylinder(const t_ray *r, const t_hittables *htbl,
		const float max_t)
{
	t_hit_record	hr;
	float			closest_t;
	t_cylinder		*hit;

	closest_t = max_t + 1.0f;
	hit_all_cylinders(r, &closest_t, htbl, &hr);
	hit_all_cylinder_caps(r, &closest_t, htbl, &hr);
	if (closest_t > max_t)
		return (false);
	hit = htbl->cylinders + hr.index;
	if (hit->mat.transparency > 0.5f)
		return (false);
	return (true);
}

inline static bool	shadow_plane(const t_ray *r, const t_hittables *htbl,
		const float max_t)
{
	t_hit_record	hr;
	float			closest_t;
	t_plane			*hit;

	closest_t = max_t + 1.0f;
	hit_all_planes(r, &closest_t, htbl, &hr);
	if (closest_t > max_t)
		return (false);
	hit = htbl->planes + hr.index;
	if (hit->mat.transparency == 0.5f)
		return (false);
	return (true);
}

inline static bool	hit_anything(const t_ray r, const t_hittables *htbl,
		const float max_t)
{
	if (htbl->sphere_count && shadow_sphere(&r, htbl, max_t))
		return (true);
	if (htbl->cylinder_count && shadow_cylinder(&r, htbl, max_t))
		return (true);
	if (htbl->plane_count && shadow_plane(&r, htbl, max_t))
		return (true);
	return (false);
}

float	count_light(const t_vec3f normal, t_vec3f hp,
		const t_lights *light, const t_hittables *htbl)
{
	t_vec3f	hp_to_light;
	t_vec3f	light_dir;
	float	intensity;
	float	diffuse;
	float	max_t;

	hp = vv_add(hp, vt_mul(normal, EPSILON));
	hp_to_light = vv_sub(light->point_center, hp);
	intensity = light->ambient_brightness;
	max_t = v_length(&hp_to_light);
	light_dir = unit_vector(hp_to_light);
	if (hit_anything((t_ray){hp, light_dir}, htbl, max_t))
		return (intensity);
	diffuse = dot(&normal, &light_dir);
	if (diffuse > 0.0f)
		intensity += light->point_brightness * diffuse;
	return (intensity);
}
