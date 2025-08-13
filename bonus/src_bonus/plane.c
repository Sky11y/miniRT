#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static inline bool	hit_plane(const t_plane *p, const t_ray *r,
						float *current_t)
{
	t_vec3f	oc;
	float	ray_plane_dot;

	oc = vv_sub(p->pos, r->origin);
	ray_plane_dot = dot(&r->direction, &p->orientation);
	if (fabsf(ray_plane_dot) < EPSILON)
		return (false);
	*current_t = dot(&oc, &p->orientation) / ray_plane_dot;
	return (*current_t > EPSILON);
}

void	hit_all_planes(const t_ray *r, float *closest_t,
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
		if (hit_plane(p + i, r, &current_t) && current_t < *closest_t)
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
