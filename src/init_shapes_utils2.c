#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

int	count_values(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	rt_cleanup(t_master *master)
{
	free(master->lights);
	free(master->camera);
}

char	*get_line(char *type, char *file, int size)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_first(line, type, size))
		{
			get_next_line(-1);
			break ;
		}
		free(line);
	}
	close(fd);
	if (!line)
		return (NULL);
	return (line);
}
