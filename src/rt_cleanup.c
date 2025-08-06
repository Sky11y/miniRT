#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

void	rt_cleanup(t_master *master)
{
	free(master->lights);
	free(master->camera);
	free(master->hittables->planes);
	free(master->hittables->spheres);
	free(master->hittables->cylinders);
}
