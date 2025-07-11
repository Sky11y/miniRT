#ifndef SHAPES_H
# define SHAPES_H

# include "mini_rt.h"

typedef struct s_sphere
{
	t_vec3f		center;
	t_vec3f		color;
	float		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3f	center;
	t_vec3f	axis_v;
	t_vec3f	base;
	t_vec3f	color;
	float	radius;
	float	radius_squared;
	float	height;
}	t_cylinder;

typedef struct s_plane
{
	t_vec3f	pos;
	t_vec3f	orientation;
	t_vec3f	color;
}	t_plane;

#endif
