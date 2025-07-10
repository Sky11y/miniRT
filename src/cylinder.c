#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

//t[0] = t0, t[1] = t1, t[2] = closest_t
//arr[0] = a, arr[1] = b, arr[2] = c, arr[3] = discriminant
static inline float	cy_hitpoints(float *arr)
{
	float	sqrt_d;
	float	near;
	float	far;

	sqrt_d = sqrtf(arr[3]);
	near = (-arr[1] - sqrt_d) / (2 * arr[0]);
	if (near > 1e-8)
		return (near);
	far = (-arr[1] + sqrt_d) / (2 * arr[0]);
	if (far > 1e-8)
		return (far);
	return (-1.0f);
}

//arr[0] = a, arr[1] = b, arr[2] = c, arr[3] = discriminant,
//arr[4] = closest_t, arr[5] = proj
//vec[0] = cylinder normalized axis vector
//vec[1]...vec[3] helpers to count coefficent
static inline float	hit_cylinder(const t_cylinder *c, const t_ray r)
{
	t_vec3f			vec[4];
	t_vec3f			between;
	float			arr[6];

	vec[0] = c->axis_v;
	vec[1] = vv_sub(r.origin, c->center);
	vec[2] = vv_sub(r.direction, vt_mul(vec[0], dot(r.direction, vec[0])));
	vec[3] = vv_sub(vec[1], vt_mul(vec[0], dot(vec[1], vec[0])));
	arr[0] = dot(vec[2], vec[2]);
	arr[1] = 2 * dot(vec[2], vec[3]);
	arr[2] = dot(vec[3], vec[3]) - c->radius_squared;
	arr[3] = arr[1] * arr[1] - (4 * arr[0] * arr[2]);
	if (arr[3] < 0.0)
		return (-1.0);
	if (arr[3] > 0)
		arr[4] = cy_hitpoints(arr);
	else
		arr[4] = -arr[1] / (2 * arr[0]);
	if (arr[4] == -1.0f)
		return (-1.0f);
	between = vv_sub(at(r, arr[4]), c->base);
	arr[5] = dot(between, vec[0]);
	if (arr[5] >= 0 && arr[5] <= c->height)
		return (arr[4]);
	return (-1.0);
}

void	hit_all_cylinders(const t_ray r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr)
{
	int					i;
	int					save;
	const int			count = htbl->cylinder_count;
	const t_cylinder	*c = htbl->cylinders;
	float				current_t;

	i = 0;
	save = -1;
	current_t = INFINITY;
	while (i < count)
	{
		current_t = hit_cylinder(c + i, r);
		if (current_t > 0 && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
			if (*closest_t < 1e-4)
				break ;
		}
		i++;
	}
	if (save == -1)
		return ;
	hr->type = cylinder;
	hr->index = save;
}
