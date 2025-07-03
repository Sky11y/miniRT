#ifndef SHAPES_H
# define SHAPES_H

# include "mini_rt.h"

typedef struct s_sphere
{
	t_vec3f		center;
	t_vec4		color;
	float		radius;
	t_material	mat;
	t_type		type;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3f	center;
	t_vec4	color;
	float	radius;
	float	height;
}	t_cylinder;

typedef struct s_plane
{
	t_vec3f	pos;
	t_vec3f	orientation;
	t_vec4	color;
}	t_plane;

#endif
