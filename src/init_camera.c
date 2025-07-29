#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_fov(char *str, t_master *master)
{
	if (is_float(str))
		return (print_error("error: invalid fov\n"));
	master->camera->fov = rt_atof(str);
	return (0);
}

static int	init_orientation(char *str, t_master *master)
{
	char	**orientation;
	int		i;

	i = 0;
	orientation = ft_split(str, ',');
	if (!orientation)
		return (print_error("error: malloc fail\n"));
	while (orientation[i])
	{
		if (is_float(orientation[i]))
		{
			free_arr(orientation);
			return (print_error("error: invalid value in camera\n"));
		}
		i++;
	}
	if (count_values(orientation) != 3)
	{
		free_arr(orientation);
		return (print_error("error: invalid camera orientation\n"));
	}
	master->camera->orientation.x = rt_atof(orientation[0]); //limits
	master->camera->orientation.y = rt_atof(orientation[1]);
	master->camera->orientation.z = rt_atof(orientation[2]);
	free_arr(orientation);
	return (0);
}

static int	init_viewpoint(char *str, t_master *master)
{
	char	**viewpoint;
	int		i;

	i = 0;
	viewpoint = ft_split(str, ',');
	if (!viewpoint)
		return (print_error("error: malloc fail\n"));
	while (viewpoint[i])
	{
		if (is_float(viewpoint[i]))
		{
			free_arr(viewpoint);
			return (print_error("error: invalid value in camera\n"));
		}
		i++;
	}
	if (count_values(viewpoint) != 3)
	{
		free_arr(viewpoint);
		return (print_error("error: invalid camera viewpoint\n"));
	}
	master->camera->center.x = rt_atof(viewpoint[0]);
	master->camera->center.y = rt_atof(viewpoint[1]);
	master->camera->center.z = rt_atof(viewpoint[2]);
	free_arr(viewpoint);
	return (0);
}

static int	init_values(char **split, t_master *master)
{
	if (count_values(split) != 4)
		return (print_error("error: invalid amount of values in camera\n"));
	if (init_viewpoint(split[1], master))
		return (1);
	if (init_orientation(split[2], master))
		return (1);
	if (init_fov(split[3], master))
		return (1);
	return (0);
}

int	init_camera(t_master *master, char *file)
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
	split = ft_multi_split(line, " \t\n");
	free(line);
	if (!split)
		return (print_error("error: malloc fail\n"));
	error = init_values(split, master);
	free_arr(split);
	return (error);
}
