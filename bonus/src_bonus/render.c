#include "mini_rt.h"
#include "scene_elements.h"

//offset[0] = x, offset[1] = y, offset[2] = total offset
t_ray	get_ray(const t_camera *cam, float x, float y)
{
	t_vec3f			offset[3];
	t_vec3f			pixel_sample;
	t_vec3f			direction;
	float			dir_off[2];

	dir_off[0] = x;
	dir_off[1] = y;
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
	return (final_color[0] << 24 | final_color[1] << 16 | final_color[2] << 8
		| 255);
}

t_vec3f	get_pixel_color_simple(const t_thread *t, int *idx)
{
	t_ray			r;

	r = get_ray(t->cam, idx[1], idx[0]);
	return (ray_color(&r, t, 2));
}
	
//idx[0] = y, idx[1] = x
//colors[1] = mixed_color, colors[0] = returned_color, colors[2] = previous_color
void	*render_thread(void *param)
{
	t_thread	*t;
	uint16_t	img_height;
	uint16_t	img_width;
	t_vec3f		final_pixel_color;
	uint32_t	colors[3];
	int			idx[2];

	t = (t_thread *)param;
	img_width = t->width;
	img_height = t->height;
	idx[0] = t->id;
	int i = 0;
	while (i < THREAD_COUNT && idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			final_pixel_color = get_pixel_color_simple(t, idx);
			colors[0] = get_color(final_pixel_color);
			t->pixels[idx[0] * img_width + idx[1]] = colors[0];
			if (idx[1] != 0)
			{
				colors[1] = mix_colors(colors[0], colors[2]);
				t->pixels[idx[0] * img_width + idx[1] - 1] = colors[1];
			}
			colors[2] = colors[0];
			if (idx[1] + 2 == img_width)
				t->pixels[idx[0] * img_width + idx[1] + 1] = colors[0];
			idx[1] += 2;
		}
		memcpy(&t->mlx_img->pixels[idx[0] * img_width * 4],
				&t->pixels[idx[0] * img_width],
				sizeof(uint32_t) * img_width);
		idx[0] += THREAD_COUNT;
		i++;
	}
	return (NULL);
}

void	*render_sharp(void *param)
{
	t_thread *t = (t_thread *)param;
	const uint16_t	img_height = t->height;
	const uint16_t	img_width = t->width;
	t_vec3f			final_pixel_color;
	int				idx[2];

	idx[0] = t->id;
	int i = 0;
	while (i < THREAD_COUNT && idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			final_pixel_color = get_pixel_color(t, idx);
			t->pixels[idx[0] * img_width + idx[1]] = get_color(final_pixel_color);
			idx[1] += 1;
		}
		memcpy(&t->mlx_img->pixels[idx[0] * img_width * 4],
				&t->pixels[idx[0] * img_width],
				sizeof(uint32_t) * img_width);
		idx[0] += THREAD_COUNT;
		i++;
	}
	return (NULL);
}
