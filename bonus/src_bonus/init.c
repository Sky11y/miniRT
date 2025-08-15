#include "scene_elements.h"

t_renderer	*init_renderer(t_renderer *r)
{
	r->rendr = false;
	r->rendr_done = false;
	return (r);
}
