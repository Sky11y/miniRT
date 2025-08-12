#include "scene_elements.h"

t_renderer	*init_renderer(t_renderer *r, t_image *i)
{
	r->image_buffer = malloc(sizeof(uint32_t) * i->image_width
			* i->image_height);
	if (!r->image_buffer)
		exit(1);
	r->rendr = false;
	r->rendr_done = false;
	return (r);
}
