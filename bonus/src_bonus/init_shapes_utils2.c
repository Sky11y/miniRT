#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static float	rt_atof_decimals(char *str, int integer, float sign)
{
	float	fraction;
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
	float	integer;
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
	if (str[i] != '.')
		return (sign * (float)integer);
	i++;
	return (rt_atof_decimals(&str[i], integer, sign));
}

int	is_float(char *str)
{
	int	i;
	int	decimal;

	i = 0;
	decimal = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		decimal = 0;
		if (str[i] == '.')
		{
			i++;
			decimal++;
		}
		if (str[i] < '0' || str[i] > '9' || decimal > 1)
			return (1);
		i++;
	}
	return (0);
}

int	count_values(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	*get_line(char *type, char **file, int size)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (file[i])
	{
		if (line_first(file[i], type, size))
		{
			line = ft_strdup(file[i]);
			if (!line)
				return (NULL);
			break ;
		}
		i++;
	}
	return (line);
}
