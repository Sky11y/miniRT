/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:24:26 by akiiski           #+#    #+#             */
/*   Updated: 2025/08/20 10:24:28 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "scene_elements.h"

float	dot(const t_vec3f u, const t_vec3f v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3f	cross(const t_vec3f u, const t_vec3f v)
{
	return ((t_vec3f){
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	});
}

t_vec3f	rotate_v(const t_vec3f v)
{
	return ((t_vec3f){-v.x, -v.y, -v.z});
}

t_vec3f	unit_vector(const t_vec3f v)
{
	const float	length = v_length(v);

	if (length < 1e-8)
		return ((t_vec3f){0, 0, 0});
	return ((t_vec3f){v.x / length, v.y / length, v.z / length});
}

t_vec3f	at(t_ray r, float t)
{
	return ((t_vec3f)vv_add(r.origin, vt_mul(r.direction, t)));
}
