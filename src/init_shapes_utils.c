#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static char	*file_to_str(int fd)
{
	char	*full_file;
	char	*line;

	full_file = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!full_file)
		{
			full_file = ft_strdup(line);
			free(line);
		}
		else
			full_file = wrap_join(full_file, line);
		if (!full_file)
		{
			print_error("error: malloc fail\n");
			return (NULL);
		}
	}
	return (full_file);
}

char	**file_to_array(char *filename)
{
	int		fd;
	char	*filestr;
	char	**file_arr;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error("error: open()\n");
		return (NULL);
	}
	filestr = file_to_str(fd);
	if (!filestr)
		return (NULL);
	close(fd);
	file_arr = ft_split(filestr, '\n');
	free(filestr);
	if (!file_arr)
	{
		print_error("error: malloc fail\n");
		return (NULL);
	}
	return (file_arr);
}

int	set_vector(t_vec3f *vec, char **values, bool limit)
{
	vec->x = rt_atof(values[0]);
	vec->y = rt_atof(values[1]);
	vec->z = rt_atof(values[2]);
	if (limit)
	{
		if (vec->x > 1.0f || vec->x < -1.0f)
		{
			free_arr(values);
			return (1);
		}
		if (vec->y > 1.0f || vec->y < -1.0f)
		{
			free_arr(values);
			return (1);
		}
		if (vec->z > 1.0f || vec->z < -1.0f)
		{
			free_arr(values);
			return (1);
		}
	}
	return (0);
}

int	string_to_color(char *str)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		num = num * 10 + str[i] - '0';
		if (num > 255)
			return (-1);
		i++;
	}
	return ((int)num);
}

void	set_colors(char *str, int i, t_vec3f *colors)
{
	int		color_value;

	color_value = 0;
	if (i < 3)
		color_value = string_to_color(str);
	if (i == 0)
		colors->x = (float)color_value / 255.0f;
	else if (i == 1)
		colors->y = (float)color_value / 255.0f;
	else if (i == 2)
		colors->z = (float)color_value / 255.0f;
}
