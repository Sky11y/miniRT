#include "mini_rt.h"
#include "scene_elements.h"

static inline uint32_t	mix_colors(uint32_t color, uint32_t prev_color)
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

//idx[0] = y, idx[1] = x, idx[2] = i
//colors[1] = mixed_color, colors[0] = returned_color, colors[2] = prev_color
static inline void	render_width(t_thread *t, uint16_t *idx, uint16_t img_width)
{
	t_vec3f		final_pixel_color;
	uint32_t	colors[3];

	while (idx[1] < img_width)
	{
		final_pixel_color = get_pixel_color(t, idx);
		colors[0] = get_color(final_pixel_color);
		mlx_put_pixel(t->mlx_img, idx[1], idx[0], colors[0]);
		if (idx[1] != 0)
		{
			colors[1] = mix_colors(colors[0], colors[2]);
			mlx_put_pixel(t->mlx_img, idx[1] - 1, idx[0], colors[1]);
		}
		colors[2] = colors[0];
		if (idx[1] + 2 == img_width)
			mlx_put_pixel(t->mlx_img, idx[1] + 1, idx[0], colors[0]);
		idx[1] += 2;
	}
}

//idx[0] = y, idx[1] = x, idx[2] = i
void	*render_thread(void *param)
{
	t_thread	*t;
	uint16_t	img_height;
	uint16_t	img_width;
	uint16_t	idx[3];
	uint16_t	i;

	t = (t_thread *)param;
	img_height = t->mlx_img->height;
	img_width = t->mlx_img->width;
	idx[0] = t->row;
	i = 0;
	while (i < THREAD_COUNT && idx[0] < img_height)
	{
		idx[1] = 0;
		render_width(t, idx, img_width);
		idx[0] += THREAD_COUNT;
		i++;
	}
	return (NULL);
}
