/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:23:36 by akiiski           #+#    #+#             */
/*   Updated: 2025/08/20 10:23:36 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static inline bool	hit_plane(const t_plane p, const t_ray r, float *current_t)
{
	const t_vec3f	oc = vv_sub(p.pos, r.origin);
	const float		ray_plane_dot = dot(r.direction, p.orientation);

	if (fabs(ray_plane_dot) < 1e-4)
		return (false);
	*current_t = dot(oc, p.orientation) / ray_plane_dot;
	if (*current_t > 1e-4)
		return (true);
	return (false);
}

void	hit_all_planes(const t_ray r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr)
{
	int				i;
	int				save;
	const int		count = htbl->plane_count;
	const t_plane	*p = htbl->planes;
	float			current_t;

	i = 0;
	save = -1;
	current_t = INFINITY;
	while (i < count)
	{
		if (hit_plane(*(p + i), r, &current_t) && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
		}
		i++;
	}
	if (save == -1)
		return ;
	hr->type = plane;
	hr->index = save;
}
