#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_fov(char *str, t_master *master)
{
	if (is_float(str))
		return (print_error("error: invalid fov\n"));
	master->camera->fov = rt_atof(str);
	if (master->camera->fov > 180 || master->camera->fov < 0)
		return (print_error("error: invalid fov\n"));
	return (0);
}

static int	init_values(char **split, t_master *master)
{
	if (count_values(split) != 4)
		return (print_error("error: invalid amount of values in camera\n"));
	if (init_vector(split[1], &master->camera->center, false))
		return (1);
	if (init_vector(split[2], &master->camera->orientation, true))
		return (1);
	if (init_fov(split[3], master))
		return (1);
	return (0);
}

int	init_camera(t_master *master, char **file)
{
	char	**split;
	char	*line;
	int		error;

	error = 0;
	master->camera = malloc(sizeof(t_camera));
	if (!(master->camera))
		return (print_error("error: malloc fail\n"));
	line = get_line("C", file, 1);
	if (!line)
		return (print_error("error: malloc fail\n"));
	split = ft_multi_split(line, " \t");
	free(line);
	if (!split)
		return (print_error("error: malloc fail\n"));
	error = init_values(split, master);
	free_arr(split);
	return (error);
}
