#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_values(char **split, t_parser *parser)
{
	t_vec3f	tint;
	t_vec3f	color;
	float	brightness;

	if (count_values(split) != 3)
		return (print_error("error: invalid amount of values in ambient\n"));
	if (init_brightness(split[1], &parser->lights->ambient_brightness))
		return (1);
	if (init_color(split[2], &parser->lights->ambient_color))
		return (1);
	color = parser->lights->ambient_color;
	brightness = parser->lights->ambient_brightness;
	tint = vt_mul(color, brightness);
	parser->lights->ambient_tint = tint;
	return (0);
}

int	init_ambient(t_parser *parser, char **file)
{
	char	**split;
	char	*line;
	int		error;

	error = 0;
	parser->lights = malloc(sizeof(t_lights));
	if (!(parser->lights))
		return (print_error("error: malloc fail\n"));
	line = get_line("A", file, 1);
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
