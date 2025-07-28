#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

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

t_vec3f	set_colors(char *str, int i)
{
	int		color_value;
	t_vec3f	colors;

	ft_memset(&colors, 0, sizeof(colors)
	color_value = 0;
	color_value = string_to_color(str);
	if (color_value == -1)
	{
		print_error("error: invalid colors\n");
		return (NULL);
	}
	if (i == 0)
		colors->x = (float)color_value;
	else if (i == 1)
		colors->y = (float)color_value;
	else if (i == 2)
		colors->z = (float)color_value;
	return (colors);
}

int	is_float(char **split)
{
	int	i;
	int	j;
	int	decimal;

	i = 1;
	decimal = 0;
	while (split[i])
	{
		j = 0;
		decimal = 0;
		while (split[i][j])
		{
			if (split[i][j] == '.' || split[i][j] == ',')
			{
				j++;
				if (split[i][j] == '.')
					decimal++;
			}
			if (split[i][j] < '0' || split[i][j] > '9' || decimal > 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
