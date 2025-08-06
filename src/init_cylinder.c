#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_height(char *str, float *height)
{
	if (is_float(str))
		return (print_error("error: invalid values\n"));
	*height = rt_atof(str);
	return (0);
}

static int	init_values(char **split, t_cylinder *cylinders)
{
	float	height;
	t_vec3f	axis_v;
	t_vec3f	center;

	if (count_values(split) != 6)
		return (print_error("error: invalid amount of values in cylinders\n"));
	if (init_vector(split[1], &cylinders->center, false))
		return (1);
	if (init_vector(split[2], &cylinders->axis_v, true))
		return (1);
	if (init_radius(split[3], &cylinders->radius))
		return (1);
	if (init_height(split[4], &cylinders->height))
		return (1);
	if (init_color(split[5], &cylinders->color))
		return (1);
	cylinders->axis_v = unit_vector(cylinders->axis_v);
	height = cylinders->height;
	axis_v = cylinders->axis_v;
	center = cylinders->center;
	cylinders->base = vv_sub(center, vt_mul(axis_v, height / 2.0f));
	cylinders->radius_squared = cylinders->radius * cylinders->radius;
	return (0);
}

static int	search_file(t_parser *parser, char **file)
{
	int		i;
	int		j;
	int		error;
	char	**split;

	j = 0;
	i = 0;
	error = 0;
	while (file[i] && error == 0)
	{
		if (line_first(file[i], "cy", 2))
		{
			split = ft_multi_split(file[i], " \t");
			if (!split)
				return (print_error("error: malloc fail\n"));
			error = init_values(split, &parser->hittables->cylinders[j]);
			free_arr(split);
			j++;
		}
		i++;
	}
	return (error);
}

int	init_cylinder(t_parser *parser, char **file)
{
	t_cylinder	*cylinders;
	int			error;

	error = 0;
	cylinders = malloc(parser->hittables->cylinder_count * sizeof(t_cylinder));
	if (!cylinders)
		return (print_error("error: malloc fail\n"));
	parser->hittables->cylinders = cylinders;
	error = search_file(parser, file);
	return (error);
}
