#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

//Glass, metal, mirror, diffuse, plastic 

int	init_material(char *str, t_material *mat)
{
	if (ft_strcmp(str, "glass") == 0)
		set_material(mat, 0.05f, 0.95f, 1.5f);
	else if (ft_strcmp(str, "metal") == 0)
		set_material(mat, 0.9f, 0.0f, 0.0f);
	else if (ft_strcmp(str, "brass") == 0)
		set_material(mat, 0.4f, 0.0f, 0.0f);
	else if (ft_strcmp(str, "mirror") == 0)
		set_material(mat, 1.0f, 0.0f, 0.0f);
	else if (ft_strcmp(str, "diffuse") == 0)
		set_material(mat, 0.0f, 0.0f, 0.0f);
	else if (ft_strcmp(str, "plastic") == 0)
		set_material(mat, 0.1f, 0.8f, 1.5f);
	else if (ft_strcmp(str, "water") == 0)
		set_material(mat, 0.05f, 0.9f, 1.33f);
	else
		return (print_error("error: invalid values\n"));
	return (0);
}

int	init_vector(char *str, t_vec3f *vector, bool limit)
{
	char	**values;
	int		i;

	i = 0;
	values = ft_split(str, ',');
	if (!values)
		return (print_error("error: malloc fail\n"));
	while (values[i])
	{
		if (is_float(values[i]))
		{
			free_arr(values);
			return (print_error("error: invalid values\n"));
		}
		i++;
	}
	if (count_values(values) != 3)
	{
		free_arr(values);
		return (print_error("error: invalid values\n"));
	}
	if (set_vector(vector, values, limit))
		return (print_error("error: invalid values\n"));
	free_arr(values);
	return (0);
}

int	init_radius(char *str, float *radius)
{
	if (is_float(str))
		return (print_error("error: invalid radius\n"));
	*radius = rt_atof(str) / 2.0f;
	return (0);
}

int	init_brightness(char *str, float *brightness)
{
	if (is_float(str))
		return (print_error("error: invalid brightness value\n"));
	*brightness = rt_atof(str);
	if (*brightness < 0.0f || *brightness > 1.0f)
		return (print_error("error: invalid brightness value\n"));
	return (0);
}

int	init_color(char *str, t_vec3f *color)
{
	char	**split;
	int		i;
	int		error;

	i = 0;
	error = 0;
	split = ft_split(str, ',');
	if (!split)
		return (print_error("error: malloc fail\n"));
	while (split[i])
	{
		set_colors(split[i], i, color);
		i++;
	}
	free_arr(split);
	if (color->x < 0.0f
		|| color->y < 0.0f
		|| color->z < 0.0f
		|| i != 3)
	{
		print_error("error: invalid colors\n");
		error = 1;
	}
	return (error);
}
