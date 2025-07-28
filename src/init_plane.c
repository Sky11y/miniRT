#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_pos(char *str, t_master *master)
{
	char	**split;

	if (isfloat(str))
		return (1);
	split = ft_split(str, ',');
	if (!split)
		return (print_error("error: malloc fail\n"));
	while (split[i])
	{
		if (i == 0)
			hittables->planes->pos->x = rt_atof(split[i]);
		if (i == 1)
			hittables->planes->pos->y = rt_atof(split[i]);
		if (i == 2)
			hittables->planes->pos->z = rt_atof(split[i]);
		if (i > 2)
			break ;
	}
	free_arr(split);
	if (i > 2)
		return (print_error("error: invalid plane\n"));
	return (0);
}

static int	init_orientation(char *str, t_master *master)
{
	char	**split;

	if (isfloat(str))
		return (1);
	split = ft_split(str, ',');
	if (!split)
		return (print_error("error: malloc fail\n"));
	while (split[i])
	{
		if (i == 0)
			hittables->planes->orientation->x = rt_atof(split[i]);
		if (i == 1)
			hittables->planes->orientation->y = rt_atof(split[i]);
		if (i == 2)
			hittables->planes->orientation->z = rt_atof(split[i]);
		if (i > 2)
			break ;
	}
	free_arr(split);
	if (i > 2)
		return (print_error("error: invalid plane\n"));
	return (0);
}

static int	init_color(char *str, t_master *master)
{
	char	**split;
	int		i;
	int		error;

	i = 0;
	error = 0;
	split = ft_split(str, ',');
	if (!split)
		return (print_error("error: malloc fail\n"));
	while (split[i] && i < 3)
	{
		if (master->hittables[hittables->i]->plane_color == NULL) //??
		{
			error = 1;
			break ;
		}
		i++;
	}
	free_arr(split);
	return (error);
}

int	init_plane(char *line, t_master *master)
{
	char	**split;
	int		i;
	int		error;

	error = 0;
	split = ft_multisplit(line, " \t");
	if (!split)
		return (print_error("error: malloc fail\n"));
	i = 1;
	while (split[i] && i < 4 && error != 0)
	{
		if (i == 1)
			error = init_pos(split[i], master);
		if (i == 2)
			error = init_orientation(split[i], master);
		if (i == 3)
			error = init_color(split[i], master);
		if (i > 3)
		{
			error = 1;
			print_error("error: ambient has too many variables\n");
		}
		i++;
	}
	free_arr(split);
	return (error);
}
