#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_values(char **split, t_plane *plane)
{
	if (count_values(split) < 4 || count_values(split) > 5)
		return (print_error("error: invalid amount of values in plane\n"));
	if (init_vector(split[1], &plane->pos, false))
		return (1);
	if (init_vector(split[2], &plane->orientation, true))
		return (1);
	if (init_color(split[3], &plane->color))
		return (1);
	if (split[4])
	{
		if (init_material(split[4], &plane->mat))
			return (1);
	}
	else
		set_material(&plane->mat, 0.0f, 0.0f, 0.0f);
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
		if (line_first(file[i], "pl", 2))
		{
			split = ft_multi_split(file[i], " \t");
			if (!split)
				return (print_error("error: malloc fail\n"));
			error = init_values(split, &parser->hittables->planes[j]);
			free_arr(split);
			j++;
		}
		i++;
	}
	return (error);
}

int	init_plane(t_parser *parser, char **file)
{
	t_plane	*planes;
	int		error;

	error = 0;
	planes = malloc(parser->hittables->plane_count * sizeof(t_plane));
	if (!planes)
		return (print_error("error: malloc fail\n"));
	parser->hittables->planes = planes;
	error = search_file(parser, file);
	return (error);
}
