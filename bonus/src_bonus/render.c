#include "mini_rt.h"
#include "scene_elements.h"

//offset[0] = x, offset[1] = y, offset[2] = total offset
t_ray	get_ray(const t_camera *cam, float x, float y)
{
	t_vec3f			offset[3];
	t_vec3f			pixel_sample;
	t_vec3f			direction;
	float			dir_off[2];

	dir_off[0] = x + random_range(0.0, 1.0);
	dir_off[1] = y + random_range(0.0, 1.0);
	offset[0] = vt_mul(cam->pixel_delta_u, dir_off[0]);
	offset[1] = vt_mul(cam->pixel_delta_v, dir_off[1]);
	offset[2] = vv_add(offset[0], offset[1]);
	pixel_sample = vv_add(cam->pixel00_center, offset[2]);
	direction = unit_vector(vv_sub(pixel_sample, cam->center));
	return ((t_ray){cam->center, direction});
}

uint32_t	mix_colors(uint32_t color, uint32_t prev_color)
{
	uint8_t	rgb_color[3];
	uint8_t	rgb_prev_color[3];
	uint8_t	final_color[3];

	rgb_color[0] = (color >> 24) & 0xFF;
	rgb_color[1] = (color >> 16) & 0xFF;
	rgb_color[2] = (color >> 8) & 0xFF;
	rgb_prev_color[0] = (prev_color >> 24) & 0xFF;
	rgb_prev_color[1] = (prev_color >> 16) & 0xFF;
	rgb_prev_color[2] = (prev_color >> 8) & 0xFF;
	final_color[0] = (rgb_color[0] + rgb_prev_color[0]) >> 1;
	final_color[1] = (rgb_color[1] + rgb_prev_color[1]) >> 1;
	final_color[2] = (rgb_color[2] + rgb_prev_color[2]) >> 1;
	return (final_color[0] << 24 | final_color[1] << 16 | final_color[2] << 8 | 255);

}

//idx[0] = y, idx[1] = x
void	render(t_master *master, mlx_image_t *mlx_img)
{
	const uint16_t	img_height = master->img->image_height;
	const uint16_t	img_width = master->img->image_width;
	const float		pixel_samples_scale = 1.0f / SAMPLES_PER_PIXEL;
	t_vec3f			final_pixel_color;
	uint32_t		mixed_color = 0;
	uint32_t		color;
	uint32_t		prev_color = 0;
	int				idx[2];

	idx[0] = 0;
	while (idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			final_pixel_color = get_pixel_color(master->htbl,
					master->cam, idx, master->light);
			color = get_color(vt_mul(final_pixel_color, pixel_samples_scale));
			mlx_put_pixel(mlx_img, idx[1], idx[0], color);
			if (idx[1] != 0)
			{
				mixed_color = mix_colors(color, prev_color);
				mlx_put_pixel(mlx_img, idx[1] - 1, idx[0], mixed_color);
			}
			prev_color = color;
			if (idx[1] + 2 == img_width)
				mlx_put_pixel(mlx_img, idx[1] + 1, idx[0], color);
			idx[1] += 2;
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
