#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_values(char **split, t_parser *parser)
{
	if (count_values(split) != 4)
		return (print_error("error: invalid amount of values in light\n"));
	if (init_vector(split[1], &parser->lights->point_center, false))
		return (1);
	if (init_brightness(split[2], &parser->lights->point_brightness))
		return (1);
	if (init_color(split[3], &parser->lights->point_color))
		return (1);
	return (0);
}

int	init_light(t_parser *parser, char **file)
{
	char	**split;
	char	*line;
	int		error;

	error = 0;
	line = get_line("L", file, 1);
	if (!line)
		return (print_error("error: malloc fail\n"));
	split = ft_multi_split(line, " \t");
	free(line);
	if (!split)
		return (print_error("error: malloc fail\n"));
	error = init_values(split, parser);
	free_arr(split);
	return (error);
}
