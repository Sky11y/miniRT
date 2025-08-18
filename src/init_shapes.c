#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_line(t_parser *parser, char **file)
{
	if (init_ambient(parser, file))
		return (1);
	if (init_camera(parser, file))
		return (1);
	if (init_light(parser, file))
		return (1);
	if (init_plane(parser, file))
		return (1);
	if (init_sphere(parser, file))
		return (1);
	if (init_cylinder(parser, file))
		return (1);
	return (0);
}

int	init_shapes(char *filename, t_parser *parser)
{
	char	**file;
	int		error;

	error = 0;
	file = file_to_array(filename);
	if (!file)
		return (1);
	error = init_line(parser, file);
	free_arr(file);
	return (error);
}
