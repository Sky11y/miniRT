#include "mini_rt.h"
#include "scene_elements.h"

int	string_to_color(char *str)
{
	int		i;
	size_t	num;

	i = 0;
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

static float	rt_atof_decimals(char *str, int integer, float sign)
{
	int		fraction;
	int		i;
	size_t	fraction_power;

	i = 0;
	fraction = 0;
	fraction_power = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fraction_power *= 10;
		fraction = fraction * 10 + str[i] - '0';
		i++;
	}
	return (sign * (integer + (float)fraction / fraction_power));
}

float	rt_atof(char *str)
{
	int		integer;
	int		i;
	float	sign;

	sign = 1.;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = -1.;
		i++;
	}
	integer = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		integer = integer * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	return (rt_atof_decimals(&str[i], integer, sign));
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
