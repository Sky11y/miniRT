#include "mini_rt.h"
#include "scene_elements.h"

static void	render_width_sharp(t_thread *t, uint16_t *idx, uint16_t img_width)
{
	t_vec3f			final_pixel_color;

	while (idx[1] < img_width)
	{
		final_pixel_color = get_pixel_color(t, idx);
		mlx_put_pixel(t->mlx_img, idx[1], idx[0], get_color(final_pixel_color));
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
	img_height = t->mlx_img->height;
	img_width = t->mlx_img->width;
	idx[0] = t->row;
	i = 0;
	while (i < THREAD_COUNT && idx[0] < img_height)
	{
		idx[1] = 0;
		render_width_sharp(t, idx, img_width);
		idx[0] += THREAD_COUNT;
		i++;
	}
	return (NULL);
}
