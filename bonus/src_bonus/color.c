#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static t_vec3f	reflection(const t_ray *r, const t_thread *t,
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

static t_vec3f	refraction(const t_ray *r, const t_thread *t,
		const t_hit_record *hr, uint8_t depth)
{
	t_ray	refracted_ray;
	t_vec3f	refracted_color;

	refracted_ray.direction = refractDir(r->direction, hr->normal, hr->ior, hr->face);
	if (v_length(&refracted_ray.direction) <= 0.0f)
		return ((t_vec3f){0, 0, 0});
	refracted_ray.direction = unit_vector(refracted_ray.direction);
	refracted_ray.origin = vv_sub(hr->hitpoint, vt_mul(hr->normal, EPSILON));
	refracted_color = ray_color(&refracted_ray, t, depth - 1);
	return (refracted_color);
}

static t_vec3f reflect_and_refract(const t_ray *r, const t_thread *t,
		const t_hit_record *hr, uint8_t depth)
{
	t_vec3f	reflected_color;
	t_vec3f	refracted_color;
	t_vec3f	combined_color;
	t_vec3f	transparent_color;
	float	kr;

	refracted_color = (t_vec3f){0, 0, 0};
	//kr = schlick_prob(r->direction, hr->normal, hr->ior);
	fresnel(r->direction, hr->normal, hr->ior, &kr);
	if (kr < 1.0f)
		refracted_color = refraction(r, t, hr, depth);
	reflected_color = reflection(r, t, hr, depth);
	combined_color = vv_add(vt_mul(reflected_color, kr),
		vt_mul(refracted_color, 1.0f - kr));
	//return (combined_color);
	transparent_color = vt_mul(combined_color, hr->transparency);
	return (transparent_color); 
}


t_vec3f	ray_color(const t_ray *r, const t_thread *t, uint8_t depth)
{
	const t_hittables	*htbl = t->htbl;
	t_hit_record		hr;
	t_vec3f				color;
	float				closest_t;
	float				light_int;

	closest_t = INFINITY;
	if (htbl->sphere_count)
		hit_all_spheres(r, &closest_t, htbl, &hr);
	if (htbl->cylinder_count)
	{
		hit_all_cylinders(r, &closest_t, htbl, &hr);
		hit_all_cylinder_caps(r, &closest_t, htbl, &hr);
	}
	if (htbl->plane_count)
		hit_all_planes(r, &closest_t, htbl, &hr);
	if (closest_t == INFINITY)
		return (t->light->ambient_tint);
	update_hr(htbl, &hr, r, closest_t);
	light_int = count_light(hr.normal, hr.hitpoint, t->light, htbl);
	if (depth == 0 || (hr.transparency == 0.0f && hr.reflect == 0.0f))
		return (vt_mul(hr.albedo, light_int));
	if (hr.transparency == 0.0f && hr.reflect > 0.0f)
		return (vv_add(reflection(r, t, &hr, depth), vt_mul(hr.albedo, light_int)));
	color = reflect_and_refract(r, t, &hr, depth);
	t_vec3f diffuse = vt_mul(hr.albedo, light_int * (1.0f - hr.transparency));
	return (vv_add(color, diffuse));
}

t_vec3f	get_pixel_color(const t_thread *t, int *idx)
{
	t_vec3f			pixel_color;
	t_ray			r;

	r = get_ray(t->cam, idx[1], idx[0]);
	pixel_color = ray_color(&r, t, MAX_RAYS);
	return (pixel_color);
}

//rgb[0] = r, rgb[1] = g, rgb[2] = b
//rgb_byte[0] = rbyte, rgb_byte[1] = gbyte, rgb_byte[2] = bbyte
uint32_t	get_color(const t_vec3f pixel_color)
{
	float	rgb[3];
	uint8_t	rgb_byte[3];

	if (pixel_color.x > 0.0)
		rgb[0] = sqrtf(pixel_color.x);
	else
		rgb[0] = 0;
	if (pixel_color.y > 0.0)
		rgb[1] = sqrtf(pixel_color.y);
	else
		rgb[1] = 0;
	if (pixel_color.z > 0.0)
		rgb[2] = sqrtf(pixel_color.z);
	else
		rgb[2] = 0;
	rgb_byte[0] = (int)(256 * clamp(rgb[0], 0, 0.999));
	rgb_byte[1] = (int)(256 * clamp(rgb[1], 0, 0.999));
	rgb_byte[2] = (int)(256 * clamp(rgb[2], 0, 0.999));
	return (rgb_byte[0] << 24 | rgb_byte[1] << 16 | rgb_byte[2] << 8 | 255);
}
