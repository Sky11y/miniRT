#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

//arr[0] = a, arr[1] = h, arr[2] = c, arr[3] = discriminant
static inline bool	hit_sphere(const t_sphere *s, const t_ray *r, int *face,
		float *current_t)
{
	float	arr[4];
	float	sqrt_d;
	t_vec3f	oc;

	oc = vv_sub(s->center, r->origin);
	arr[0] = v_length_squared(&r->direction);
	arr[1] = dot(&r->direction, &oc);
	arr[2] = v_length_squared(&oc) - s->radius_squared;
	arr[3] = arr[1] * arr[1] - arr[0] * arr[2];
	if (arr[3] < EPSILON)
		return (false);
	sqrt_d = sqrtf(arr[3]);
	*current_t = (arr[1] - sqrt_d) / arr[0];
	if (*current_t > EPSILON)
	{
		*face = 1;
		return (true);
	}
	*current_t = (arr[1] + sqrt_d) / arr[0];
	if (*current_t > EPSILON)
	{
		*face = -1;
		return (true);
	}
	return (false);
}

//save[0] = index of sphere, save[1] = face of sphere
void	hit_all_spheres(const t_ray *r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr)
{
	int				i;
	int				save[2];
	const int		count = htbl->sphere_count;
	const t_sphere	*s = htbl->spheres;
	float			current_t;

	i = 0;
	save[0] = -1;
	save[1] = 0;
	current_t = INFINITY;
	while (i < count)
	{
		if (hit_sphere(s + i, r, &save[1], &current_t)
			&& current_t < *closest_t)
		{
			*closest_t = current_t;
			save[0] = i;
			hr->face = save[1];
		}
		i++;
	}
	if (save[0] == -1)
		return ;
	hr->index = save[0];
	hr->type = sphere;
}
