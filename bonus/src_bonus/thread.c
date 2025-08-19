#include "mini_rt.h"
#include "scene_elements.h"

static inline t_thread	init_thread(t_master *m, size_t i, uint16_t row)
{
	t_thread	t;

	t.row = i + row;
	t.cam = m->cam;
	t.htbl = m->htbl;
	t.light = m->light;
	t.mlx_img = m->mlx_img;
	return (t);
}

int	create_threads(t_master *m, t_renderer *r, int frame, bool sharp)
{
	const uint16_t	starting_row = THREAD_COUNT * THREAD_COUNT * frame;
	size_t			i;

	r->rendr = true;
	i = 0;
	while (i < THREAD_COUNT)
	{
		r->args[i] = init_thread(m, i, starting_row);
		if (sharp)
		{
			if (pthread_create(&r->threads[i], NULL, render_sharp, &r->args[i]))
				return (1);
		}
		else
		{
			if (pthread_create(&r->threads[i], NULL, render_thread,
					&r->args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	join_threads(t_renderer *r)
{
	size_t	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		if (pthread_join(r->threads[i], NULL))
			return (1);
		i++;
	}
	r->rendr = false;
	return (0);
}
