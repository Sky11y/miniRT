#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

//arr[0] = a, arr[1] = h, arr[2] = c, arr[3] = discriminant
static inline float	hit_sphere(const t_sphere s, const t_ray r)
{
	float	arr[4];
	float	sqrt_d;
	float	t[2];
	t_vec3f	oc;

	oc = vv_sub(s.center, r.origin);
	arr[0] = v_length_squared(r.direction);
	arr[1] = dot(r.direction, oc);
	arr[2] = v_length_squared(oc) - s.radius * s.radius;
	arr[3] = arr[1] * arr[1] - arr[0] * arr[2];
	if (arr[3] < 0.0)
		return (-1.0f);
	sqrt_d = sqrtf(arr[3]);
	t[0] = (arr[1] - sqrt_d) / arr[0];
	if (t[0] > 1e-4)
		return (t[0]);
	t[1] = (arr[1] + sqrt_d) / arr[0];
	if (t[1] > 1e-4)
		return (t[1]);
	return (-1.0f);
}

void	hit_all_spheres(const t_ray r, float *closest_t,
		const t_hittables *htbl, t_hit_record *hr)
{
	int				i;
	int				save;
	const int		count = htbl->sphere_count;
	const t_sphere	*s = htbl->spheres;
	float			current_t;

	i = 0;
	save = -1;
	current_t = INFINITY;
	while (i < count)
	{
		current_t = hit_sphere(*(s + i), r);
		if (current_t > 1e-4 && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
			if (*closest_t < 1e-8)
				break ;
		}
		i++;
	}
	if (save == -1)
		return ;
	hr->type = sphere;
	hr->index = save;
}
