/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:30:13 by akiiski           #+#    #+#             */
/*   Updated: 2025/08/20 10:30:13 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "scene_elements.h"

inline float	v_length(const t_vec3f *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

inline float	v_length_squared(const t_vec3f *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}
