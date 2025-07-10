#include "mini_rt.h"
#include "scene_elements.h"

static int	print_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	return (1);
}

static int	validate_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strcmp(&filename[len - 3], ".rt"))
		return (1);
	return (0);
}

static bool	line_first(char *line, char *value, int len)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line[i]) && line[i] != '\n')
		i++;
	if (!ft_strncmp(&line[i], value, len))
		return (true);
	return (false);
}

static int	check_limitations(t_master *master)
{
	if (master->amb_count > 1)
		return (print_error("error: too many ambients\n"));
	if (master->cam_count > 1)
		return (print_error("error: too many cameras\n"));
	if (master->lig_count > 1)
		return (print_error("error: too many light\n"));
	if (master->hittables->plane_count > 10)
		return (print_error("error: too many planes\n"));
	if (master->hittables->sphere_count > 10)
		return (print_error("error: too many spheres\n"));
	if (master->hittables->cylinder_count > 10)
		return (print_error("error: too many cylinders\n"));
	return (0);
}

static int	parse_line(char *line, t_master *master)
{
	if (line_first(line, "A", 1))
		master->amb_count++;
	else if (line_first(line, "C", 1))
		master->cam_count++;
	else if (line_first(line, "L", 1))
		master->lig_count++;
	else if (line_first(line, "pl", 2))
		master->hittables->plane_count++;
	else if (line_first(line, "sp", 2))
		master->hittables->sphere_count++;
	else if (line_first(line, "cy", 2))
		master->hittables->cylinder_count++;
	else if (line_first(line, "\n", 1))
		return (0);
	else
		return (print_error("error: invalid file\n"));
	return (check_limitations(master));
}

int	parse_file(int argc, char *filename, t_master *master)
{
	int		file_fd;
	int		error;
	char	*line;

	error = 0;
	if (argc != 2)
		return (print_error("error: argument\n"));
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
		error = parse_line(line, master);
		free(line);
		if (error >= 1)
			return (1);
	}
	if (master->amb_count == 0 || master->lig_count == 0)
		return (print_error("error: must have 1 ambient and light\n"));
	return (0);
}
