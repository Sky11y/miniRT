/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:32:56 by jpiensal          #+#    #+#             */
/*   Updated: 2025/07/02 13:17:40 by jpiensal         ###   ########.fr       */
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
	return (t_vec3f){u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x};
}

t_vec3f rotate_v(const t_vec3f v)
{
	return (t_vec3f){-v.x, -v.y, -v.z};
}

t_vec3f	unit_vector(const t_vec3f v)
{
	const float length = v_length(v);
	if (length < 1e-8)
		return (t_vec3f){0, 0, 0};
	return (t_vec3f){v.x / length, v.y / length, v.z / length};
}


float v_length(const t_vec3f v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float v_length_squared(const t_vec3f v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3f vt_multiply(const t_vec3f v, float t)
{
	return (t_vec3f){v.x * t, v.y * t, v.z * t};
}

t_vec3f vt_division(const t_vec3f v, float t)
{
	if (fabs(t) < 1e-8)
		return (t_vec3f){0, 0, 0};
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

t_vec3f random_v()
{
	return (t_vec3f){random_float(), random_float(), random_float()};
}


t_vec3f random_v_range(float min, float max)
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
		p = random_v_range(-1, 1);
		lensq = v_length_squared(p);
		if (1e-8 < lensq && lensq <= 1.0)
			return (vt_division(p, sqrt(lensq)));
	}
}

t_vec3f random_on_hemisphere(const t_vec3f normal)
{
	t_vec3f on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0)
		return (on_unit_sphere);
	return (rotate_v(on_unit_sphere));
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
	if (x < 0.0f)
		return (0.0f);
	if (x > 1.0f)
		return (1.0f);
	return (x);
}

float degrees_to_rad(float degrees)
{
	return degrees * PI / 180.0;
}

