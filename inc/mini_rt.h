#ifndef MINI_RT_H
# define MINI_RT_H

# include <unistd.h>		//open, close, read, write, exit
# include <stdlib.h>		//malloc, free
# include <stdio.h>		//printf, perror
# include <string.h> 	//strerror
# include <math.h> 		//all the math
# include <stdint.h> 	//explicit int values
# include <limits.h>	//INT_MAX
# include <stdbool.h>	//true and false
# include <time.h>		//REMOVE THIS!!!! only used for randomness

# define PI 3.1415926535

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

t_vec3f	vt_multiply(const t_vec3f v, float t);
t_vec3f	vt_division(const t_vec3f v, float t);
t_vec3f	vv_add(const t_vec3f u, const t_vec3f v);
t_vec3f	vv_sub(const t_vec3f u, const t_vec3f v);

/* HELPERS */
t_vec3f random_v();
t_vec3f random_v_range(float min, float max);
t_vec3f	random_unit_vector(void);
t_vec3f random_on_hemisphere(const t_vec3f normal);
float	random_float( void );
float	random_range(float min, float max);
float	clamp(const float x);
float	degrees_to_rad(float degrees);

/* RENDER */
void	write_color(const t_vec3f pixel_color);

#endif
