#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

//arr[0] = a, arr[1] = b, arr[2] = c, arr[3] = discriminant
static inline bool	cy_hitpoints(float *arr, int *face, float *current_t)
{
	float	sqrt_d;

	sqrt_d = sqrtf(arr[3]);
	*current_t = (-arr[1] - sqrt_d) / (2 * arr[0]);
	if (*current_t > EPSILON)
	{
		*face = 1;
		return (true);
	}
	*current_t = (-arr[1] + sqrt_d) / (2 * arr[0]);
	if (*current_t > EPSILON)
	{
		*face = -1;
		return (true);
	}
	return (false);
}

//arr[0] = a, arr[1] = b, arr[2] = c, arr[3] = discriminant, arr[4] = proj
//vec[0] = cylinder normalized axis vector
//vec[1...3] are helpers to count coefficents
static inline bool	hit_cylinder(const t_cylinder *c, const t_ray *r, int *face,
		float *current_t)
{
	t_vec3f			vec[4];
	t_vec3f			between;
	float			arr[5];

	vec[0] = c->axis_v;
	vec[1] = vv_sub(r->origin, c->center);
	vec[2] = vv_sub(r->direction, vt_mul(vec[0], dot(&r->direction, &vec[0])));
	vec[3] = vv_sub(vec[1], vt_mul(vec[0], dot(&vec[1], &vec[0])));
	arr[0] = dot(&vec[2], &vec[2]);
	arr[1] = 2 * dot(&vec[2], &vec[3]);
	arr[2] = dot(&vec[3], &vec[3]) - c->radius_squared;
	arr[3] = arr[1] * arr[1] - (4 * arr[0] * arr[2]);
	if (arr[3] < EPSILON)
		return (false);
	if (!cy_hitpoints(arr, face, current_t))
		return (false);
	between = vv_sub(at(r, *current_t), c->base);
	arr[4] = dot(&between, &vec[0]);
	return (arr[4] >= 0 && arr[4] <= c->height);
}

//save[0] = index of cylinder, save[1] = face of cylinder
void	hit_all_cylinders(const t_ray *r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr)
{
	int					i;
	int					save[2];
	const int			count = htbl->cylinder_count;
	const t_cylinder	*c = htbl->cylinders;
	float				current_t;

	i = 0;
	save[0] = -1;
	save[1] = 0;
	current_t = INFINITY;
	while (i < count)
	{
		if (hit_cylinder(c + i, r, &save[1], &current_t)
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
	hr->type = cylinder;
	hr->index = save[0];
}
