#include "mini_rt.h"
#include "scene_elements.h"

extern FILE *infolog;
//offset[0] = x, offset[1] = y, offset[2] = total offset
t_ray	get_ray(const t_camera *cam, int *idx)
{
	t_vec3f			offset[3];
	t_vec3f			pixel_sample;
	t_vec3f			direction;
	float			dir_off[2];

	dir_off[0] = random_range(0.0, 1.0);
	dir_off[1] = random_range(0.0, 1.0);
	offset[0] = vt_mul(cam->pixel_delta_v, (float)idx[0] + dir_off[0]);
	offset[1] = vt_mul(cam->pixel_delta_u, (float)idx[1] + dir_off[1]);
	offset[2] = vv_add(offset[0], offset[1]);
	pixel_sample = vv_add(cam->pixel00_center, offset[2]);
	direction = unit_vector(vv_sub(pixel_sample, cam->center));
	return ((t_ray){cam->center, direction});
}

//idx[0] = y, idx[1] = x
void	render(const t_hittables *htbl, const t_camera *cam,
		const t_image *img, const t_lights *light)
{
	const uint16_t	img_height = img->image_height;
	const uint16_t	img_width = img->image_width;
	const float		pixel_samples_scale = 1.0f / cam->samples_per_pixel;
	t_vec3f			final_pixel_color;
	int				idx[2];

	idx[0] = 0;
	while (idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			final_pixel_color = get_pixel_color(htbl, cam, idx, light);
			write_color(vt_mul(final_pixel_color, pixel_samples_scale));
			idx[1] += 1;
		}
		idx[0] += 1;
	}
}

t_vec3f	reflect(const t_vec3f v, const t_vec3f n)
{
	t_vec3f	tmp;

	tmp = vt_mul(n, 2 * dot(v, n));
	return (vv_sub(v, tmp));
}
