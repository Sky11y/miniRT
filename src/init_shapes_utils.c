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
	if (str[i] != '.')
		return (sign * (float)integer);
	i++;
	return (rt_atof_decimals(&str[i], integer, sign));
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
		colors->x = (float)color_value;
	else if (i == 1)
		colors->y = (float)color_value;
	else if (i == 2)
		colors->z = (float)color_value;
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
