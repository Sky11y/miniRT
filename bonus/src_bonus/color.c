#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

static void reflect_ray(t_ray *new_ray, t_vec3f dir, t_hit_record *hr)
{
	new_ray->direction = unit_vector(reflect(dir, hr->normal));
	new_ray->origin = vv_add(hr->hitpoint, vt_mul(hr->normal, 1e-4));
}

void	fresnel(const t_vec3f v, const t_vec3f n, const float ior, float *kr)
{
	float cosi = clamp(dot(v, n), -1.0, 1.0);
	float etai = 1.0f;
	float etat = ior;

	if (cosi > 0) {
		float temp = etai;
		etai = etat;
		etat = temp;
	}
	float sint = etai / etat * sqrtf(fmaxf(0.0f, 1 - cosi * cosi));
	if (sint >= 1)
		*kr = 1;
	else
	{
		float cost = sqrtf(fmaxf(0.0f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*kr = (Rs * Rs + Rp * Rp) / 2;
	}
}

static t_vec3f refractDir(const t_vec3f v, const t_vec3f n, const float ior,
		const int front_face)
{
	float cosi = clamp(dot(n, v), -1.0f, 1.0f);
	float etai = 1.0f;
	float etat = ior;
	t_vec3f normal = n;

	if (front_face == -1)
	{
		cosi = -cosi;
		float temp = etai;
		etai = etat;
		etat = temp;
		normal = rotate_v(normal);
	}
	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0.0)
		return (t_vec3f){0, 0, 0};
	return (vv_add(vt_mul(v, eta), vt_mul(n, eta * cosi - sqrt(k))));
}

inline static float	schlick_prob(const t_vec3f v, const t_vec3f n, const float ior)
{
	float	r0;
	float	cosi = clamp(dot(v, n), -1.0f, 1.0f);
	float	etai = 1.0f;
	float	etat = ior;

	if (cosi > 0.0f)
	{
		float temp = etai;
		etai = etat;
		etat = temp;
		cosi = -cosi;
	}
	r0 = (etai - etat) / (etai + etat);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * powf(1.0f - fabsf(cosi), 5.0f);
}

t_vec3f	ray_color(const t_ray *r, const t_hittables *htbl,
		const t_lights *light, uint8_t depth)
{
	t_hit_record	hr;
	t_vec3f			color;
	float			closest_t;
	float			light_intensity;
	t_ray			new_ray;

	closest_t = INFINITY;
	light_intensity = 0;
	if (htbl->sphere_count)
		hit_all_spheres(r, &closest_t, htbl, &hr);
	if (htbl->cylinder_count)
	{
		hit_all_cylinders(r, &closest_t, htbl, &hr);
		hit_all_cylinder_caps(r, &closest_t, htbl, &hr);
	}
	if (htbl->plane_count)
		hit_all_planes(r, &closest_t, htbl, &hr);
	if (closest_t == INFINITY)
		return (light->ambient_tint);
	update_hr(htbl, &hr, r, closest_t);
	light_intensity = count_light(hr.normal, hr.hitpoint, light, htbl);
	if (depth <= 0)
		return (vt_mul(hr.albedo, light_intensity));
	else if (hr.transparency == 0.0f && hr.reflect > 0.0f)
	{
		reflect_ray(&new_ray, r->direction, &hr);
		color = vt_mul(ray_color(&new_ray, htbl, light, depth - 1), hr.reflect);
		return (vv_add(color, vt_mul(hr.albedo, light_intensity)));
	}
	else if (hr.transparency > 0.0f)
	{
		t_vec3f refractionColor = (t_vec3f){0, 0, 0};
		//fresnel(r.direction, hr.normal, 1.5f, &hr.kr);
		hr.kr = schlick_prob(r->direction, hr.normal, 1.5f);
		t_vec3f bias = vt_mul(hr.normal, 1e-4);
		if (hr.kr < 1)
		{
			new_ray.direction = refractDir(r->direction, hr.normal, 1.5f, hr.face);
			if (v_length(new_ray.direction) > 0.0f)
			{
				new_ray.direction = unit_vector(new_ray.direction);
				new_ray.origin = vv_sub(hr.hitpoint, bias);
				refractionColor = ray_color(&new_ray, htbl, light, depth - 1);
			}
		}
		new_ray.direction = reflect(r->direction, hr.normal);
		new_ray.origin = vv_add(hr.hitpoint, bias);
		t_vec3f reflectionColor = ray_color(&new_ray, htbl, light, depth - 1);
		color = vv_add(vt_mul(reflectionColor, hr.kr), vt_mul(refractionColor, 1 - hr.kr));
		color = vt_mul(color, hr.transparency);
		t_vec3f diffuse = vt_mul(hr.albedo, light_intensity * (1.0f - hr.transparency));
		return (vv_add(color, diffuse));
	}
	return (vt_mul(hr.albedo, light_intensity));
}

t_vec3f	get_pixel_color(const t_hittables *htbl, const t_camera *cam,
		int *idx, const t_lights *light)
{
	t_vec3f			pixel_color;
	t_vec3f			ret_color;
	uint16_t		sample_no;
	t_ray			r;

	pixel_color.x = 0;
	pixel_color.y = 0;
	pixel_color.z = 0;
	sample_no = 0;
	while (sample_no < SAMPLES_PER_PIXEL)
	{
		r = get_ray(cam, idx[1], idx[0]);
		ret_color = ray_color(&r, htbl, light, MAX_RAYS);
		pixel_color = vv_add(pixel_color, ret_color);
		sample_no += 1;
	}
	return (pixel_color);
}

//rgb[0] = r, rgb[1] = g, rgb[2] = b
//rgb_byte[0] = rbyte, rgb_byte[1] = gbyte, rgb_byte[2] = bbyte
uint32_t	get_color(const t_vec3f pixel_color)
{
	float	rgb[3];
	uint8_t	rgb_byte[3];

	if (pixel_color.x > 0.0)
		rgb[0] = sqrtf(pixel_color.x);
	else
		rgb[0] = 0;
	if (pixel_color.y > 0.0)
		rgb[1] = sqrtf(pixel_color.y);
	else
		rgb[1] = 0;
	if (pixel_color.z > 0.0)
		rgb[2] = sqrtf(pixel_color.z);
	else
		rgb[2] = 0;
	rgb_byte[0] = (int)(256 * clamp(rgb[0], 0, 0.999));
	rgb_byte[1] = (int)(256 * clamp(rgb[1], 0, 0.999));
	rgb_byte[2] = (int)(256 * clamp(rgb[2], 0, 0.999));
	return (rgb_byte[0] << 24 | rgb_byte[1] << 16 | rgb_byte[2] << 8 | 255);
}
