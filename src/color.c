#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

t_vec3f	ray_color(const t_ray r, const t_hittables *htbl, const t_lights *light)
{
	t_hit_record	hr;
	float			closest_t;
	float			light_intensity;

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
	if (closest_t != INFINITY)
	{
		update_hr(htbl, &hr, r, closest_t);
		light_intensity = count_light(hr.normal, hr.hitpoint, light);
		return (vt_mul(hr.albedo, light_intensity));
	}
	return (light->ambient_tint);
}

t_vec3f	get_pixel_color(const t_hittables *htbl, const t_camera *cam,
		int *idx, const t_lights *light)
{
	const uint16_t	samples = cam->samples_per_pixel;
	t_vec3f			pixel_color;
	uint16_t		sample_no;
	t_ray			r;

	pixel_color.x = 0;
	pixel_color.y = 0;
	pixel_color.z = 0;
	sample_no = 0;
	while (sample_no < samples)
	{
		r = get_ray(cam, idx);
		pixel_color = vv_add(pixel_color, ray_color(r, htbl, light));
		sample_no += 1;
	}
	return (pixel_color);
}

//rgb[0] = r, rgb[1] = g, rgb[2] = b
//rgb_byte[0] = rbyte, rgb_byte[1] = gbyte, rgb_byte[2] = bbyte
void	write_color(const t_vec3f pixel_color)
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
	printf("%d %d %d\n", rgb_byte[0], rgb_byte[1], rgb_byte[2]);
}
