#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_fov(char *str, t_master *master)
{
	if (is_float(str))
		return (print_error("error: invalid fov\n"));
	master->camera->fov = rt_atof(str);
	if (master->camera->fov > 180.0f || master->camera->fov < 0.0f)
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

static void	init_default_camera(t_master *master)
{
	master->camera->center.x = 0.0f;
	master->camera->center.y = 0.0f;
	master->camera->center.z = 0.0f;
	master->camera->orientation.x = 0.0f;
	master->camera->orientation.y = 0.0f;
	master->camera->orientation.z = 1.0f;
	master->camera->fov = 70.0f;
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
	if (master->cam_count == 0)
		init_default_camera(master);
	else
	{
		line = get_line("C", file, 1);
		if (!line)
			return (print_error("error: malloc fail\n"));
		split = ft_multi_split(line, " \t");
		free(line);
		if (!split)
			return (print_error("error: malloc fail\n"));
		error = init_values(split, master);
		free_arr(split);
	}
	return (error);
}
