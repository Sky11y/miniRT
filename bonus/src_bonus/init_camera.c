#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static int	init_fov(char *str, t_parser *parser)
{
	if (is_float(str))
		return (print_error("error: invalid fov\n"));
	parser->camera->fov = rt_atof(str);
	if (parser->camera->fov > 180.0f || parser->camera->fov < 0.0f)
		return (print_error("error: invalid fov\n"));
	return (0);
}

static int	init_values(char **split, t_parser *parser)
{
	if (count_values(split) != 4)
		return (print_error("error: invalid amount of values in camera\n"));
	if (init_vector(split[1], &parser->camera->center, false))
		return (1);
	if (init_vector(split[2], &parser->camera->orientation, true))
		return (1);
	if (init_fov(split[3], parser))
		return (1);
	parser->camera->orientation = unit_vector(parser->camera->orientation);
	parser->camera->vup = (t_vec3f){0, 1.0f, 0};
	parser->camera->yaw = atan2f(parser->camera->orientation.z,
			parser->camera->orientation.x);
	parser->camera->pitch = asinf(parser->camera->orientation.y);
	return (0);
}

static void	init_default_camera(t_parser *parser)
{
	parser->camera->center.x = 0.0f;
	parser->camera->center.y = 0.0f;
	parser->camera->center.z = 0.0f;
	parser->camera->orientation.x = 0.0f;
	parser->camera->orientation.y = 0.0f;
	parser->camera->orientation.z = 1.0f;
	parser->camera->fov = 70.0f;
	parser->camera->vup = (t_vec3f){0, 1.0f, 0};
	parser->camera->yaw = atan2f(parser->camera->orientation.z,
			parser->camera->orientation.x);
	parser->camera->pitch = asinf(parser->camera->orientation.y);
}

int	init_camera(t_parser *parser, char **file)
{
	char	**split;
	char	*line;
	int		error;

	error = 0;
	parser->camera = malloc(sizeof(t_camera));
	if (!(parser->camera))
		return (print_error("error: malloc fail\n"));
	if (parser->cam_count == 0)
		init_default_camera(parser);
	else
	{
		line = get_line("C", file, 1);
		if (!line)
			return (print_error("error: malloc fail\n"));
		split = ft_multi_split(line, " \t");
		free(line);
		if (!split)
			return (print_error("error: malloc fail\n"));
		error = init_values(split, parser);
		free_arr(split);
	}
	return (error);
}
