#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

t_ray	get_new_ray(const t_ray r, t_hit_record *hr, t_scatter_type *scatter_type)
{
	const t_vec3f	normal = hr->normal;
	t_ray			new_ray;
	t_vec3f			new_dir;
	t_vec3f			scattered;
	float scattered_normal;

	new_dir = new_ray_dir(r.direction, normal, hr, &scatter_type);
	scattered = vv_add(new_dir, random_unit_vector());
	scattered_normal = dot(scattered, normal);
	if ((scatter_type == REFLECT && scattered_normal < 1e-4) ||
		(scatter_type == REFRACT && scattered_normal > -1e-4))
		scattered = new_dir;
	new_ray.direction = unit_vector(scattered);
	if (scatter_type == REFRACT)
		new_ray.origin = vv_sub(hr->hitpoint, vt_mul(normal, 1e-4));
	else
		new_ray.origin = vv_add(hr->hitpoint, vt_mul(normal, 1e-4));
	return (new_ray);
}

t_vec3f	ray_color(const t_ray r, const t_hittables *htbl,
		const t_lights *light, uint8_t depth)
{
	t_hit_record	hr;
	float			closest_t;
	float			light_intensity;
	t_ray			new_ray;
	t_vec3f			color;
	t_scatter_type	scatter_type;

	closest_t = INFINITY;
	light_intensity = 0;
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
		return (light->ambient_tint);
	update_hr(htbl, &hr, r, closest_t);
	light_intensity = count_light(hr.normal, hr.hitpoint, light, htbl);
	if (depth <= 0 || hr.mat == DIFFUSE)
		return (vt_mul(hr.albedo, light_intensity));
	new_ray = get_new_ray(r, &hr, &scatter_type);
	color = ray_color(new_ray, htbl, light, depth - 1);
	if (scatter_type == REFRACT)
		return vv_add(vt_mul(vt_mul(hr.albedo, light_intensity), 0.0f), vt_mul(color, 1));
	return vv_add(vt_mul(vt_mul(hr.albedo, light_intensity), 0.5f), vt_mul(color, hr.reflect));
}

t_vec3f	get_pixel_color(const t_hittables *htbl, const t_camera *cam,
		int *idx, const t_lights *light)
{
	const uint16_t	samples = SAMPLES_PER_PIXEL;
	const uint8_t	depth = MAX_RAYS;
	t_vec3f			pixel_color;
	t_vec3f			ret_color;
	uint16_t		sample_no;
	t_ray			r;

	pixel_color.x = 0;
	pixel_color.y = 0;
	pixel_color.z = 0;
	sample_no = 0;
	while (sample_no < samples)
	{
		r = get_ray(cam, idx[1], idx[0]);
		ret_color = ray_color(r, htbl, light, depth);
		pixel_color = vv_add(pixel_color, ret_color);
		sample_no += 1;
	}
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
