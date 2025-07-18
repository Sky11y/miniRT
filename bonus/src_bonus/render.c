#include "mini_rt.h"
#include "scene_elements.h"

extern FILE *infolog;
//offset[0] = x, offset[1] = y, offset[2] = total offset
t_ray	get_ray(const t_camera *cam, int *idx)
{
	t_vec3f			offset[3];
	t_vec3f			pixel_sample;
	t_vec3f			direction;
	float			dir_off[2];

	dir_off[0] = random_range(0.0, 1.0);
	dir_off[1] = random_range(0.0, 1.0);
	offset[0] = vt_mul(cam->pixel_delta_v, (float)idx[0] + dir_off[0]);
	offset[1] = vt_mul(cam->pixel_delta_u, (float)idx[1] + dir_off[1]);
	offset[2] = vv_add(offset[0], offset[1]);
	pixel_sample = vv_add(cam->pixel00_center, offset[2]);
	direction = unit_vector(vv_sub(pixel_sample, cam->center));
	return ((t_ray){cam->center, direction});
}

//idx[0] = y, idx[1] = x
void	render(const t_hittables *htbl, const t_camera *cam,
		const t_image *img, const t_lights *light)
{
	const uint16_t	img_height = img->image_height;
	const uint16_t	img_width = img->image_width;
	const float		pixel_samples_scale = 1.0f / cam->samples_per_pixel;
	t_vec3f			final_pixel_color;
	int				idx[2];

	idx[0] = 0;
	while (idx[0] < img_height)
	{
		idx[1] = 0;
		while (idx[1] < img_width)
		{
			final_pixel_color = get_pixel_color(htbl, cam, idx, light);
			write_color(vt_mul(final_pixel_color, pixel_samples_scale));
			idx[1] += 1;
		}
		idx[0] += 1;
	}
}

t_vec3f	reflect(const t_vec3f v, const t_vec3f n)
{
	t_vec3f	tmp;

	tmp = vt_mul(n, 2 * dot(v, n));
	return (vv_sub(v, tmp));
}

t_vec3f refract(const t_vec3f v, const t_vec3f n, const float eta,
		const float cos_theta)
{
	t_vec3f	tmp1;
	t_vec3f	tmp2;
	float	tmp3;
	t_vec3f	tmp4;
	float	k;

	k = 1.0f - eta * eta * (1.0f - cos_theta * cos_theta);
	if (k < 0.0f){
		return ((t_vec3f){0, 0, 0});
	}
	tmp1 = vv_add(v, vt_mul(n, cos_theta));
	tmp2 = vt_mul(tmp1, eta);
	tmp3 = sqrtf(fabs(1.0f - v_length_squared(tmp2)));
	tmp4 = vt_mul(n, tmp3 * -1.0f);
	return (vv_add(tmp2, tmp4));
	//tmp1 = vt_mul(v, eta);
	//tmp2 = vt_mul(n, eta * cos_theta - sqrtf(k));
	//return (vv_add(tmp1, tmp2));
}

inline static bool	schlick_prob(const float cos_theta, const float eta)
{
	float	r0;
	float	prob;

	r0 = (1.0f - eta) / (1.0f + eta);
	r0 = r0 * r0;
	prob = r0 + (1.0f - r0) * powf(1.0f - cos_theta, 5);
	return (prob > random_range(0.0f, 1.0f));
}

t_vec3f	new_ray_dir(const t_vec3f v, const t_vec3f n,
		const t_hit_record *hr, t_scatter_type *type)
{
	float	cos_theta; 
	float	sin_theta;
	float	eta;

	if (hr->mat != GLASS)
	{
		*type = REFLECT;
		return (reflect(v, n));
	}
	if (hr->face == 1)
		eta = 0.67f;
	else
		eta = 1.5f;
	cos_theta = fminf(-dot(v, n), 1.0f);
	sin_theta = sqrtf(1.0f - cos_theta * cos_theta);
	if (eta * sin_theta > 1.0f || schlick_prob(cos_theta, eta))
	{
		*type = REFLECT;
		return (reflect(v, n));
	}
	*type = REFRACT;
	return (refract(v, n, eta, cos_theta));
}
