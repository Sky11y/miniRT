#include "mini_rt.h"
#include "scene_elements.h"

//rgb[0] = r, rgb[1] = g, rgb[2] = b
//rgb_byte[0] = rbyte, rgb_byte[1] = gbyte, rgb_byte[2] = bbyte
inline static int	get_color(const t_vec3f pixel_color)
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

inline static t_vec3f	ray_color(const t_ray r, const t_hittables *htbl,
		const t_lights *light)
{
	t_hit_record	hr;
	float			closest_t;
	float			light_intensity;
	const uint8_t	shape_count[3] = {htbl->sphere_count, htbl->cylinder_count,
		htbl->plane_count};

	closest_t = INFINITY;
	light_intensity = 0;
	if (shape_count[0])
		hit_all_spheres(r, &closest_t, htbl, &hr);
	if (shape_count[1])
	{
		hit_all_cylinders(r, &closest_t, htbl, &hr);
		hit_all_cylinder_caps(r, &closest_t, htbl, &hr);
	}
	if (shape_count[2])
		hit_all_planes(r, &closest_t, htbl, &hr);
	if (closest_t != INFINITY)
	{
		update_hr(htbl, &hr, r, closest_t);
		light_intensity = count_light(hr.normal, hr.hitpoint, light, htbl);
		return (vt_mul(hr.albedo, light_intensity));
	}
	return (light->ambient_tint);
}

//offset[0] = x, offset[1] = y, offset[2] = total offset
inline static t_ray	get_ray(const t_camera *cam, float x, float y)
{
	t_vec3f			offset[3];
	t_vec3f			pixel_sample;
	t_vec3f			direction;

	offset[0] = vt_mul(cam->pixel_delta_v, y);
	offset[1] = vt_mul(cam->pixel_delta_u, x);
	offset[2] = vv_add(offset[0], offset[1]);
	pixel_sample = vv_add(cam->pixel00_center, offset[2]);
	direction = unit_vector(vv_sub(pixel_sample, cam->center));
	return ((t_ray){cam->center, direction});
}

//idx[0] = y, idx[1] = x
void	render(t_master *master, mlx_image_t *mlx_img)
{
	const uint16_t	img_height = master->img->image_height;
	const uint16_t	img_width = master->img->image_width;
	int				idx[2];
	int				color;
	t_ray			r;

	idx[0] = 0;
	while (idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			r = get_ray(master->cam, idx[1], idx[0]);
			color = get_color(ray_color(r, master->htbl, master->light));
			mlx_put_pixel(mlx_img, idx[1], idx[0], color);
			idx[1] += 1;
		}
		idx[0] += 1;
	}
}
