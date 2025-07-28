#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

int	is_float(char **split)
{
	int	i;
	int	j;
	int	decimal;

	i = 1;
	decimal = 0;
	while (split[i])
	{
		j = 0;
		decimal = 0;
		while (split[i][j])
		{
			if (split[i][j] == '.' || split[i][j] == ',')
			{
				j++;
				if (split[i][j] == '.')
					decimal++;
			}
			if (split[i][j] < '0' || split[i][j] > '9' || decimal > 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	set_colors(char *str, t_master *master, int i)
{
	int	error;

	error = 0;
	error = string_to_color(str);
	if (error == -1)
		return (print_error("error: invalid colors\n"));
	if (i == 0)
		colors->x = (float)error;
	else if (i == 1)
		colors->y = (float)error;
	else if (i == 2)
		colors->z = (float)error;
	}
	return (0);
}

static int	init_color(char *str, t_master *master)
{
	char	**split;
	int		i;
	int		error;
	t_vec3f	colors;

	i = 0;
	error = 0;
	split = ft_split(str, ',');
	if (!split)
		return (print_error("error: malloc fail\n"));
	while (split[i] && i < 3)
	{
		error = set_colors(split[i], master, i);
		if (error == 1)
			break ;
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
		free_arr(split);
	}
	return (error);
}
