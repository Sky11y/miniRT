#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

int	init_plane(char *line, t_master *master)
{
	char	**split;
	int		i;
	int		error;

	error = 0;
	split = ft_multisplit(line, " \t");
	if (!split)
		return (print_error("error: malloc fail\n"));
	i = 1;
	while (split[i] && i < 3 && error != 0)
	{
		if (i == 1)
			error = init_brightness(split[i], master);
		if (i == 2)
			error = init_color(split[i], master);
		if (i > 2)
		{
			error = 1;
			print_error("error: ambient has too many variables\n");
		}
		i++;
	}
	free_arr(split);
	return (error);
}
