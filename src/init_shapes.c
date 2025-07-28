#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_line(char *line, t_master *master)
{
	int	error;

	error = 0;
	if (line_first(line, "A", 1))
		error = init_ambient(line, master);
	/*
	else if (line_first(line, "C", 1))
		error = init_camera(line, master);
	*/
	else if (line_first(line, "L", 1))
		error = init_light();
	/*
	else if (line_first(line, "pl", 2))
		error = init_plane(line, master);
	else if (line_first(line, "sp", 2))
		error = init_sphere();
	else if (line_first(line, "cy", 2))
		error = init_cylinder();
		*/
	else if (line_first(line, "\n", 1))
		return (0);
	else
		error = init_hittables;
	return (error);
}

static void	allocate_objects(t_master *master)
{
	uint8_t	obj_count;

	obj_count = master->hittables->obj_count;
	master->hittables = malloc(obj_count * sizeof(t_hittables) + 1);
	if (!master->hittables)
		return ;
	master->hittables[obj_count] = NULL;
}

int	init_shapes(int argc, char *filename, t_master *master)
{
	int		file_fd;
	int		error;
	char	*line;

	error = 0;
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (print_error("error: open()\n"));
	allocate_objects(master);
	while (true)
	{
		line = get_next_line(file_fd);
		if (line == NULL)
			break ;
		error = init_line(line, master);
		free(line);
		if (error >= 1)
			break ;
	}
	close(file_fd);
	return (error);
}
