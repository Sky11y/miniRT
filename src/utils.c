/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:32:56 by jpiensal          #+#    #+#             */
/*   Updated: 2025/06/30 16:33:15 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "scene_elements.h"

float 	dot(const t_vec3f u, const t_vec3f v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3f	cross(const t_vec3f u, const t_vec3f v)
{
	return (t_vec3f){u.y * v.z - u.z * v.x,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x};
}

t_vec3f	unit_vector(const t_vec3f v)
{
	return (t_vec3f){v.x / v_length(v), 
			v.y / v_length(v),
			 v.z / v_length(v)};
}

float v_length(const t_vec3f v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3f vt_multiply(const t_vec3f v, float t)
{
	return (t_vec3f){v.x * t, v.y * t, v.z * t};
}

t_vec3f vt_division(const t_vec3f v, float t)
{
	return (t_vec3f){v.x / t, v.y / t, v.z / t};
}

t_vec3f vv_add(const t_vec3f u, const t_vec3f v)
{
	return (t_vec3f){u.x + v.x, u.y + v.y, u.z + v.z};
}

t_vec3f vv_sub(const t_vec3f u, const t_vec3f v)
{
	return (t_vec3f){u.x - v.x, u.y - v.y, u.z - v.z};
}

t_vec3f at(t_ray r, float t)
{
	return (t_vec3f)vv_add(r.origin, vt_multiply(r.direction, t));
}

float degreet_to_rad(float degrees)
{
	return degrees * PI / 180.0;
}

float random_float( void )
{
	return (float)rand() / ((float)RAND_MAX + 1.0f);
}

float random_range(float min, float max)
{
	return min + (max - min) * random_float();
}

float clamp(const float x)
{
	return (x > 1 ? 1.0 : x);
}

t_vec3f random_vector(float min, float max)
{
	return (t_vec3f){ random_range(min, max),
					  random_range(min, max),
					  random_range(min, max) };
}

t_vec3f random_unit_vector()
{
	t_vec3f p;
	float lensq;

	while (true)
	{
		p = random_vector(-1, 1);
		lensq = v_length(p) * v_length(p);
		if (lensq < 1.0)
			return (vt_division(p, sqrt(lensq)));
	}
}
