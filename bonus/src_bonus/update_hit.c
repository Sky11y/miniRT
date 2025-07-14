#include "mini_rt.h"
#include "scene_elements.h"

static inline void	sphere_hr(const t_hittables *htbl, t_hit_record *hr)
{
	t_sphere	final_s;

	final_s = *(htbl->spheres + hr->index);
	hr->albedo = final_s.color;
	hr->fuzz = final_s.fuzz;
	hr->reflect = final_s.reflect;
	if (final_s.front_face == true)
		hr->normal = unit_vector(vv_sub(hr->hitpoint, final_s.center));
	else
		hr->normal = unit_vector(vv_sub(final_s.center, hr->hitpoint));
}

static inline void	cylinder_hr(const t_hittables *htbl, t_hit_record *hr)
{
	t_cylinder	*final_c;
	t_vec3f		v;
	t_vec3f		projected;
	float		proj;

	final_c = htbl->cylinders + hr->index;
	hr->albedo = final_c->color;
	hr->fuzz = final_c->fuzz;
	hr->reflect = final_c->reflect;
	v = vv_sub(hr->hitpoint, final_c->base);
	proj = dot(v, final_c->axis_v);
	projected = vt_mul(final_c->axis_v, proj);
	hr->normal = unit_vector(vv_sub(v, projected));
}

static inline void	cylinder_cap_hr(const t_hittables *htbl, t_hit_record *hr,
		const t_ray r)
{
	t_cylinder	*final_c;

	final_c = htbl->cylinders + hr->index;
	hr->albedo = final_c->color;
	hr->fuzz = final_c->fuzz;
	hr->reflect = final_c->reflect;
	hr->normal = unit_vector(final_c->axis_v);
	if (dot(r.direction, hr->normal) > 0.0f)
		hr->normal = rotate_v(hr->normal);
}

static inline void	plane_hr(const t_hittables *htbl, t_hit_record *hr,
		const t_ray r)
{
	t_plane		final_p;

	final_p = *(htbl->planes + hr->index);
	hr->albedo = final_p.color;
	hr->fuzz = final_p.fuzz;
	hr->reflect = final_p.reflect;
	hr->normal = unit_vector(final_p.orientation);
	if (dot(r.direction, hr->normal) > 0.0f)
		hr->normal = rotate_v(hr->normal);
}

void	update_hr(const t_hittables *htbl, t_hit_record *hr,
		const t_ray r, const float t)
{
	hr->hitpoint = at(r, t);
	if (hr->type == sphere)
		sphere_hr(htbl, hr);
	else if (hr->type == cylinder)
		cylinder_hr(htbl, hr);
	else if (hr->type == cylinder_cap)
		cylinder_cap_hr(htbl, hr, r);
	else if (hr->type == plane)
		plane_hr(htbl, hr, r);
}
