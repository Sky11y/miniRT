#include "mini_rt.h"

int	validate_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strcmp(&filename[len - 3], ".rt"))
		return (1);
	return (0);
}

int	parse_file(int argc, char *filename)
{
	int	file_fd;

	if (argc != 2)
	{
		ft_putstr_fd("error: argument\n", 2);
		return (1);
	}
	if (validate_filename(filename))
	{
		ft_putstr_fd("error: filename\n", 2);
		return (1);
	}
	file_fd = open(
	return (0);
}
