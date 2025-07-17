#ifndef SHAPES_H
# define SHAPES_H

# include "mini_rt.h"

//sizeof(t_vec3f) = 12 bytes (sizeof(float) * 3)
//size = t_vec3f * 2 + float = 2 * 12 + 4 = 28 bytes 
typedef struct s_sphere
{
	t_vec3f		center;
	t_vec3f		color;
	float		radius;
	t_mat_type	mat;
}	t_sphere;

//size = t_vec3f * 4 + float * 3 = 4 * 12 + 3 * 4 = 60 bytes
typedef struct s_cylinder
{
	t_vec3f	center;
	t_vec3f	axis_v;
	t_vec3f	base;
	t_vec3f	color;
	float	radius;
	float	radius_squared;
	float	height;
	float	fuzz;
	float	reflect;
	t_mat_type	mat;
}	t_cylinder;

//size = t_vec3f * 3 = 3 * 12 = 36 bytes
typedef struct s_plane
{
	t_vec3f	pos;
	t_vec3f	orientation;
	t_vec3f	color;
	float	fuzz;
	float	reflect;
	t_mat_type	mat;
}	t_plane;

#endif
