#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>	//open, close, read, write, exit
# include <fcntl.h>		//open
# include <stdlib.h>	//malloc, free
# include <stdio.h>		//printf, perror
# include <string.h> 	//strerror
# include <math.h> 		//all the math
# include <stdint.h> 	//explicit int values
# include <stdbool.h>	//true and false
# include <pthread.h>

# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"
# include "libft.h"

# define WIN_HEIGHT 800
# define WIN_WIDTH 1600
# define MAX_RAYS 5
# define THREAD_COUNT 50
# define EPSILON 1e-2f

typedef enum e_shape
{
	sphere,
	cylinder,
	cylinder_cap,
	plane,
}	t_shape;

typedef struct s_material
{
	float	reflect;
	float	transparency;
	float	ior;
}	t_material;

typedef struct t_vec3f
{
	float	x;
	float	y;
	float	z;
}	t_vec3f;

float		inverse_sqrt(float nbr);

/* VECTOR CALCULATIONS */
float		dot(const t_vec3f *u, const t_vec3f *v);
t_vec3f		cross(const t_vec3f u, const t_vec3f v);
t_vec3f		unit_vector(const t_vec3f v);
t_vec3f		rotate_v(const t_vec3f v);
float		v_length(const t_vec3f *v);
float		v_length_squared(const t_vec3f *v);

t_vec3f		vt_mul(const t_vec3f v, float t);
t_vec3f		vt_div(const t_vec3f v, float t);
t_vec3f		vv_add(const t_vec3f u, const t_vec3f v);
t_vec3f		vv_sub(const t_vec3f u, const t_vec3f v);
t_vec3f		vv_mul(const t_vec3f v, const t_vec3f u);

/* HELPERS */
float		clamp(const float x, const float min, const float max);
float		degrees_to_rad(float degrees);
bool		near_zero(const t_vec3f v);

/* RANDOM */
float		random_float(void);
float		random_range(float min, float max);
t_vec3f		random_v(void);
t_vec3f		random_v_range(float min, float max);
t_vec3f		random_unit_vector(void);

/* RENDER */
uint32_t	get_color(const t_vec3f pixel_color);

#endif
