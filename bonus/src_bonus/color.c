#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static inline t_vec3f	final_color(const t_ray *r, const t_thread *t,
		t_hit_record *hr, uint8_t depth)
{
	t_vec3f	color;
	t_vec3f	diffuse;
	float	light_int;

	light_int = count_light(hr->normal, hr->hitpoint, t->light, t->htbl);
	if (depth == 0 || (hr->transparency == 0.0f && hr->reflect == 0.0f))
		return (vt_mul(hr->albedo, light_int));
	if (hr->transparency == 0.0f && hr->reflect > 0.0f)
	{
		return (vv_add(reflection(r, t, hr, depth),
				vt_mul(hr->albedo, light_int)));
	}
	color = reflect_and_refract(r, t, hr, depth);
	diffuse = vt_mul(hr->albedo, light_int * (1.0f - hr->transparency));
	return (vv_add(color, diffuse));
}

//offset[0] = x, offset[1] = y, offset[2] = total offset
t_ray	get_ray(const t_camera *cam, float x, float y)
{
	t_vec3f	offset[3];
	t_vec3f	pixel_sample;
	t_vec3f	direction;

	offset[0] = vt_mul(cam->pixel_delta_u, x);
	offset[1] = vt_mul(cam->pixel_delta_v, y);
	offset[2] = vv_add(offset[0], offset[1]);
	pixel_sample = vv_add(cam->pixel00_center, offset[2]);
	direction = unit_vector(vv_sub(pixel_sample, cam->center));
	return ((t_ray){cam->center, direction});
}

t_vec3f	ray_color(const t_ray *r, const t_thread *t, uint8_t depth)
{
	const t_hittables	*htbl = t->htbl;
	t_hit_record		hr;
	float				closest_t;

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
	return (final_color(r, t, &hr, depth));
}

t_vec3f	get_pixel_color(const t_thread *t, uint16_t *idx)
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

	if (pixel_color.x > 0.0f)
		rgb[0] = sqrtf(pixel_color.x);
	else
		rgb[0] = 0;
	if (pixel_color.y > 0.0f)
		rgb[1] = sqrtf(pixel_color.y);
	else
		rgb[1] = 0;
	if (pixel_color.z > 0.0f)
		rgb[2] = sqrtf(pixel_color.z);
	else
		rgb[2] = 0;
	rgb_byte[0] = (int)(255 * clamp(rgb[0], 0, 0.999));
	rgb_byte[1] = (int)(255 * clamp(rgb[1], 0, 0.999));
	rgb_byte[2] = (int)(255 * clamp(rgb[2], 0, 0.999));
	return (rgb_byte[0] << 24 | rgb_byte[1] << 16 | rgb_byte[2] << 8 | 255);
}
