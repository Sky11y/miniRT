#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_values(char **split, t_sphere *sphere)
{
	if (count_values(split) < 4 || count_values(split) > 5)
		return (print_error("error: invalid amount of values in spheres\n"));
	if (init_vector(split[1], &sphere->center, false))
		return (1);
	if (init_radius(split[2], &sphere->radius))
		return (1);
	if (init_color(split[3], &sphere->color))
		return (1);
	if (split[4])
	{
		if (init_material(split[4], &sphere->mat))
			return (1);
	}
	else
		set_material(&sphere->mat, 0.0f, 0.0f, 0.0f);
	sphere->radius_squared = sphere->radius * sphere->radius;
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
		if (line_first(file[i], "sp", 2))
		{
			split = ft_multi_split(file[i], " \t");
			if (!split)
				return (print_error("error: malloc fail\n"));
			error = init_values(split, &parser->hittables->spheres[j]);
			free_arr(split);
			j++;
		}
		i++;
	}
	return (error);
}

int	init_sphere(t_parser *parser, char **file)
{
	t_sphere	*spheres;
	int			error;

	error = 0;
	spheres = malloc(parser->hittables->sphere_count * sizeof(t_sphere));
	if (!spheres)
		return (print_error("error: malloc fail\n"));
	parser->hittables->spheres = spheres;
	error = search_file(parser, file);
	return (error);
}
