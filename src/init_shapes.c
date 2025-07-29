#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_line(t_master *master, char *file)
{
	if (init_ambient(master, file))
		return (1);
	if (init_camera(master, file))
		return (1);
	//error = init_camera(master, error, file);
	//error = init_light();
	//error = init_plane(line, master);
	//error = init_sphere();
	//error = init_cylinder();
	return (0);
}

/*
static void	allocate_objects(t_master *master)
{
	uint8_t	obj_count;

	obj_count = master->hittables->obj_count;
	master->hittables = malloc(obj_count * sizeof(t_hittables) + 1);
	if (!master->hittables)
		return ;
	master->hittables[obj_count] = NULL;
}
*/

int	init_shapes(char *filename, t_master *master)
{
	int		error;

	error = 0;
	//allocate_objects(master);
	error = init_line(master, filename);
	return (error);
}
