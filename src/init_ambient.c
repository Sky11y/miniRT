#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

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
		master->lights->ambient_colors = set_colors(split[i], master, i);
		if (master->lights->ambient_colors == NULL)
		{
			error = 1;
			break ;
		}
		i++;
	}
	free_arr(split);
	return (error);
}

static int	init_brightness(char *str, t_master *master)
{
	float	brightness;

	if (is_float(str))
		return (1);
	brightness = rt_atof(str);
	master->lights->ambient_brightness = brightness;
	return (0);
}

int	init_ambient(char *line, t_master *master)
{
	char	**split;
	int		i;
	int		error;

	error = 0;
	split = ft_multisplit(line, " \t");
	if (!split)
		return (print_error("error: malloc fail\n"));
	i = 1;
	while (split[i] && i < 3 && error != 0)
	{
		if (i == 1)
			error = init_brightness(split[i], master);
		if (i == 2)
			error = init_color(split[i], master);
		i++;
		if (i > 2)
		{
			error = 1;
			print_error("error: ambient has too many variables\n");
		}
	}
	free_arr(split);
	return (error);
}
