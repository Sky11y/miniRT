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

static int	check_limitations(t_master *master)
{
	int			obj_count;
	t_hittables	*tmp;

	tmp = master->hittables;
	if (master->amb_count > 1)
		return (print_error("error: too many ambients\n"));
	if (master->cam_count > 1)
		return (print_error("error: too many cameras\n"));
	if (master->lig_count > 1)
		return (print_error("error: too many light\n"));
	obj_count = tmp->plane_count + tmp->cylinder_count + tmp->sphere_count;
	if (obj_count > 300)
		return (print_error("error: too many objects\n"));
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
			break ;
	}
	close(file_fd);
	if (master->amb_count == 0 || master->lig_count == 0)
		return (print_error("error: must have 1 ambient and light\n"));
	return (error);
}
