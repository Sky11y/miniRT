#include "mini_rt.h"
#include "scene_elements.h"

float	rt_atof(char *str)
{
	int		i;
	float	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] == '.')
			i++;
		else
		{
			num = num * 10 + str[i] - '0';
		}
		if (num > 100)
			return (num);
		i++;
	}
}

bool	line_first(char *line, char *value, int len)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line[i]) && line[i] != '\n')
		i++;
	if (!ft_strncmp(&line[i], value, len))
		return (true);
	return (false);
}

int	print_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	return (1);
}
