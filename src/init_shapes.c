#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_line(t_master *master, char **file)
{
	if (init_ambient(master, file))
		return (1);
	if (init_camera(master, file))
		return (1);
	if (init_light(master, file))
		return (1);
	if (init_plane(master, file))
		return (1);
	return (0);
}

int	init_shapes(char *filename, t_master *master)
{
	char	**file;
	int		error;

	error = 0;
	file = file_to_array(filename);
	if (!file)
	{
		free_arr(file);
		return (1);
	}
	error = init_line(master, file);
	free_arr(file);
	return (error);
}
