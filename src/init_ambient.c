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
	while (split[i])
	{
		set_colors(split[i], i, &master->lights->ambient_color);
		i++;
	}
	free_arr(split);
	if (master->lights->ambient_color.x == -1
		|| master->lights->ambient_color.y == -1
		|| master->lights->ambient_color.z == -1
		|| i != 3)
	{
		print_error("error: invalid colors\n");
		error = 1;
	}
	return (error);
}

static int	init_brightness(char *str, t_master *master)
{
	float	brightness;

	if (is_float(str))
		return (print_error("error: invalid value in brightness\n"));
	brightness = rt_atof(str);
	if (brightness < 0 || brightness > 1)
		return (print_error("error: invalid brightness\n"));
	master->lights->ambient_brightness = brightness;
	return (0);
}

static int	init_values(char **split, t_master *master)
{
	if (count_values(split) != 3)
		return (print_error("error: invalid amount of values in ambient\n"));
	if (init_brightness(split[1], master))
		return (1);
	if (init_color(split[2], master))
		return (1);
	return (0);
}

int	init_ambient(t_master *master, char *file)
{
	char	**split;
	char	*line;
	int		error;

	error = 0;
	master->lights = malloc(sizeof(t_lights));
	if (!(master->lights))
		return (print_error("error: malloc fail\n"));
	line = get_line("A", file, 1);
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
