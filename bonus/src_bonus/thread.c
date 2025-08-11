#include "mini_rt.h"
#include "scene_elements.h"

void	create_threads(t_master *m, t_renderer *r, int frame, bool sharp)
{
	const uint16_t	starting_row = THREAD_COUNT * THREAD_COUNT * frame;
	size_t			i;

	r->rendering = true;
	i = 0;
	while (i < THREAD_COUNT)
	{
		r->args[i] = (t_thread){
			.id = i + starting_row,
			.width = m->img->image_width,
			.height = m->img->image_height,
			.pixels = r->image_buffer,
			.cam = m->cam,
			.htbl = m->htbl,
			.light = m->light,
			.mlx_img = m->mlx_img,
		};
		if (sharp)
			pthread_create(&r->threads[i], NULL, render_sharp, &r->args[i]);
		else
			pthread_create(&r->threads[i], NULL, render_thread, &r->args[i]);
		i++;
		//handle errors
	}	
}

void	join_threads(t_renderer *r)
{
	size_t	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		if (pthread_join(r->threads[i], NULL))
			exit(1);							// SOME CLEANING UP NEEDED
		i++;
	}
	r->rendering = false;
}
