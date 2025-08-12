#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static inline float	hit_cap(const t_vec3f base, const float d,
		const t_cylinder *c, const t_ray *r)
{
	t_vec3f			hp;
	t_vec3f			dd;
	float			t;
	const t_vec3f	base_to_origin = vv_sub(base, r->origin);

	t = dot(&base_to_origin, &c->axis_v) / d;
	if (t < EPSILON)
		return (-1.0f);
	hp = at(r, t);
	dd = vv_sub(hp, base);
	if (dot(&dd, &dd) > c->radius_squared)
		return (-1.0f);
	return (t);
}

static inline float	hit_cylinder_caps(const t_cylinder *c, const t_ray *r)
{
	const t_vec3f	bottom = c->base;
	const t_vec3f	top = vv_add(bottom, vt_mul(c->axis_v, c->height));
	float			t[2];
	float			d;

	d = dot(&c->axis_v, &r->direction);
	if (fabs(d) < EPSILON)
		return (-1.0);
	t[0] = hit_cap(top, d, c, r);
	t[1] = hit_cap(bottom, d, c, r);
	if (t[0] > EPSILON && (t[1] < 0 || t[0] < t[1]))
		return (t[0]);
	if (t[1] > EPSILON)
		return (t[1]);
	return (-1.0f);
}

void	hit_all_cylinder_caps(const t_ray *r, float *closest_t,
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
		current_t = hit_cylinder_caps(c + i, r);
		if (current_t > EPSILON && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
		}
		i++;
	}
	if (save == -1)
		return ;
	hr->type = cylinder_cap;
	hr->index = save;
}
