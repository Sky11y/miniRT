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

static inline t_vec3f	get_pixel_color_simple(const t_thread *t, uint16_t *idx)
{
	t_ray	r;

	r = get_ray(t->cam, idx[1], idx[0]);
	return (ray_color(&r, t, 2));
}

/*void	put_color(t_thread *t, uint16_t *idx, const t_vec3f pixel_color)
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
	uint16_t row = idx[0] * t->img_width;
	t->mlx_img->pixels[row + idx[1] * 4 + 0] = rgb_byte[0];
	t->mlx_img->pixels[row + idx[1] * 4 + 1] = rgb_byte[1];
	t->mlx_img->pixels[row + idx[1] * 4 + 2] = rgb_byte[2];
	t->mlx_img->pixels[row + idx[1] * 4 + 0] = 255;
}*/

//idx[0] = y, idx[1] = x, idx[2] = i
//colors[1] = mixed_color, colors[0] = returned_color, colors[2] = prev_color
static inline void	render_width(t_thread *t, uint16_t *idx, uint16_t img_width)
{
	t_vec3f		final_pixel_color;
	uint32_t	colors[3];

	while (idx[1] < img_width)
	{
		final_pixel_color = get_pixel_color_simple(t, idx);
		colors[0] = get_color(final_pixel_color);
		mlx_put_pixel(t->mlx_img, idx[1], idx[0], colors[0]);
		//t->pixels[idx[0] * img_width + idx[1]] = colors[0];
		if (idx[1] != 0)
		{
			colors[1] = mix_colors(colors[0], colors[2]);
			mlx_put_pixel(t->mlx_img, idx[1], idx[0], colors[1]);
			//t->pixels[idx[0] * img_width + idx[1] - 1] = colors[1];
		}
		colors[2] = colors[0];
		if (idx[1] + 2 == img_width)
			mlx_put_pixel(t->mlx_img, idx[1], idx[0], colors[0]);
			//t->pixels[idx[0] * img_width + idx[1] + 1] = colors[0];
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
	img_height = t->height;
	img_width = t->width;
	idx[0] = t->id;
	i = 0;
	while (i < THREAD_COUNT && idx[0] < img_height)
	{
		idx[1] = 0;
		render_width(t, idx, img_width);
		//memcpy(&t->mlx_img->pixels[idx[0] * img_width * 4],
		//	&t->pixels[idx[0] * img_width],
		//	sizeof(uint32_t) * img_width);
		idx[0] += THREAD_COUNT;
		i++;
	}
	return (NULL);
}
