#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>	//close, read, write, exit
# include <fcntl.h>		//open
# include <stdlib.h>	//malloc, free
# include <stdio.h>		//printf, perror
# include <string.h>	//strerror
# include <math.h>		//all the math
# include <stdint.h>	//explicit int values
# include <limits.h>	//INT_MAX
# include <stdbool.h>	//true and false
# include <time.h>		//REMOVE THIS!!!! only used for randomness
# include <libft.h>		//libft

typedef enum e_shape
{
	sphere,
	cylinder,
	cylinder_cap,
	plane,
}	t_shape;

typedef struct t_vec4
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_vec4;

typedef struct t_vec3f
{
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct t_vec2
{
	uint16_t	u;
	uint16_t	v;
}	t_vec2;

float	inverse_sqrt(float nbr);

/* VECTOR CALCULATIONS */
float	dot(const t_vec3f u, const t_vec3f v);
t_vec3f	cross(const t_vec3f u, const t_vec3f v);
t_vec3f	unit_vector(const t_vec3f v);
t_vec3f rotate_v(const t_vec3f v);
float	v_length(const t_vec3f v);
float	v_length_squared(const t_vec3f v);

t_vec3f	vt_mul(const t_vec3f v, float t);
t_vec3f	vt_div(const t_vec3f v, float t);
t_vec3f	vv_add(const t_vec3f u, const t_vec3f v);
t_vec3f	vv_sub(const t_vec3f u, const t_vec3f v);
t_vec3f	vv_mul(const t_vec3f v, const t_vec3f u);

/* HELPERS */
float	clamp(const float x, const float min, const float max);
float	degrees_to_rad(float degrees);
bool	near_zero(const t_vec3f v);

/* RENDER */
void	write_color(const t_vec3f pixel_color);

#endif
