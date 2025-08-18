#include "mini_rt.h"
#include "scene_elements.h"

static int	validate_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strcmp(&filename[len - 3], ".rt"))
		return (1);
	return (0);
}

static int	check_limitations(t_parser *parser)
{
	int			obj_count;
	t_hittables	*tmp;

	tmp = parser->hittables;
	if (parser->amb_count > 1)
		return (print_error("error: too many ambients\n"));
	if (parser->cam_count > 1)
		return (print_error("error: too many cameras\n"));
	if (parser->lig_count > 1)
		return (print_error("error: too many light\n"));
	obj_count = tmp->plane_count + tmp->cylinder_count + tmp->sphere_count;
	if (obj_count > 300)
		return (print_error("error: too many objects\n"));
	parser->hittables = tmp;
	return (0);
}

static int	parse_line(char *line, t_parser *parser)
{
	if (line_first(line, "A", 1))
		parser->amb_count++;
	else if (line_first(line, "C", 1))
		parser->cam_count++;
	else if (line_first(line, "L", 1))
		parser->lig_count++;
	else if (line_first(line, "pl", 2))
		parser->hittables->plane_count++;
	else if (line_first(line, "sp", 2))
		parser->hittables->sphere_count++;
	else if (line_first(line, "cy", 2))
		parser->hittables->cylinder_count++;
	else if (line_first(line, "\n", 1))
		return (0);
	else
		return (print_error("error: invalid file\n"));
	return (check_limitations(parser));
}

int	parse_file(char *filename, t_parser *parser)
{
	int		file_fd;
	int		error;
	char	*line;

	error = 0;
	if (validate_filename(filename))
		return (print_error("error: filename\n"));
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
		return (print_error("error: open()\n"));
	while (true)
	{
		line = get_next_line(file_fd);
		if (line == NULL)
			break ;
		error = parse_line(line, parser);
		free(line);
		if (error >= 1)
			break ;
	}
	close(file_fd);
	if (error == 0 && (parser->amb_count == 0 || parser->lig_count == 0))
		return (print_error("error: must have 1 ambient and light\n"));
	return (error);
}
