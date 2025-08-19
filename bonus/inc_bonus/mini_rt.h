#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <pthread.h>

# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"
# include "libft.h"

# define WIN_HEIGHT 800
# define WIN_WIDTH 1600
# define MAX_RAYS 3
# define THREAD_COUNT 20
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

/* HELPERS */
float		clamp(const float x, const float min, const float max);
float		degrees_to_rad(float degrees);

/* RENDER */
uint32_t	get_color(const t_vec3f pixel_color);

#endif
