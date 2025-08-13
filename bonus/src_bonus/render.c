#include "mini_rt.h"
#include "scene_elements.h"

static inline t_vec3f	get_pixel_color(const t_thread *t, uint16_t *idx)
{
	t_vec3f			pixel_color;
	t_ray			r;

	r = get_ray(t->cam, idx[1], idx[0]);
	pixel_color = ray_color(&r, t, MAX_RAYS);
	return (pixel_color);
}

static void	render_width_sharp(t_thread *t, uint16_t *idx, uint16_t img_width)
{
	t_vec3f			final_pixel_color;

	while (idx[1] < img_width)
	{
		final_pixel_color = get_pixel_color(t, idx);
		mlx_put_pixel(t->mlx_img, idx[1], idx[0], get_color(final_pixel_color));
		//t->pixels[idx[0] * img_width + idx[1]] = get_color(final_pixel_color);
		idx[1] += 1;
	}
}

void	*render_sharp(void *param)
{
	t_thread	*t;
	uint16_t	img_height;
	uint16_t	img_width;
	uint16_t	idx[2];
	uint16_t	i;

	t = (t_thread *)param;
	img_height = t->height;
	img_width = t->width;
	idx[0] = t->id;
	i = 0;
	while (i < THREAD_COUNT && idx[0] < img_height)
	{
		idx[1] = 0;
		render_width_sharp(t, idx, img_width);
		//memcpy(&t->mlx_img->pixels[idx[0] * img_width * 4],
		//	&t->pixels[idx[0] * img_width],
		//	sizeof(uint32_t) * img_width);
		idx[0] += THREAD_COUNT;
		i++;
	}
	return (NULL);
}
