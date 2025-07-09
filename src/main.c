#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

FILE *infolog;

//arr[0] = a, arr[1] = h, arr[2] = c, arr[3] = discriminant
float hit_sphere(const t_sphere s, const t_ray r)
{
	float	arr[4];
	t_vec3f oc;

	oc = vv_sub(s.center, r.origin);
	arr[0] = v_length_squared(r.direction);
	arr[1] = dot(r.direction, oc);
	arr[2] = v_length_squared(oc) - s.radius * s.radius;
	arr[3] = arr[1] * arr[1] - arr[0] * arr[2];

	if (arr[3] < 0.0)
		return (-1.0f);
	return ((arr[1] - sqrtf(arr[3]) ) / arr[0]);
}

void	hit_all_spheres(const t_ray r, float *closest_t, const t_hittables *htbl, t_hit_record *hr)
{
	int 			i;
	int 			save;
	const int		count = htbl->sphere_count;
	const t_sphere	*s = htbl->spheres;
	float			current_t;
	t_sphere		final_s;

	i = 0;
	save = -1;
	current_t = INFINITY;
	while (i < count)
	{
		current_t = hit_sphere(*(s + i), r);
		if (current_t > 0 && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
		}
		i++;
	}
	if (save > -1)
	{
		final_s = *(htbl->spheres + save);
		hr->albedo = final_s.color;
		hr->hitpoint = at(r, *closest_t);
		hr->normal = unit_vector(vv_sub(hr->hitpoint, final_s.center));
	}
}

float	hit_plane(const t_plane p, const t_ray r)
{
	float		hit;
	const float ray_plane_dot = dot(r.direction, p.orientation);
	
	if (fabs(ray_plane_dot) < 1e-8)
		return (-1);
	hit = dot(vv_sub(p.pos, r.origin), p.orientation) / ray_plane_dot;	
	if (hit >= 0)
		return (hit);
	return (-1);
}

void hit_all_planes(const t_ray r, float *closest_t, const t_hittables *htbl, t_hit_record *hr)
{
	int				i;
	int				save;
	const int		count = htbl->plane_count;
	const t_plane	*p = htbl->planes;
	float			current_t;
	t_plane			final_p;

	i = 0;
	save = -1;
	current_t = INFINITY;
	while (i < count)
	{
		current_t = hit_plane(*(p + i), r);
		if (current_t > 0 && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
		}
		i++;
	}
	if (save > -1)
	{
		final_p = *(htbl->planes + save);
		hr->albedo = final_p.color;
		hr->hitpoint = at(r, *closest_t);
		hr->normal = unit_vector(final_p.orientation);
	}
}
/*
float	hit_cylinder(const t_cylinder c, const t_ray r)
{
	const t_vec3f	n_cross_a = cross(r.direction, c.axis_v);
	const float		n_cross_a_dot = dot(n_cross_a, n_cross_a);
	const float		radius = c.diameter / 2;
	const float		radius_squared = radius * radius;
	const t_vec3f	base = vv_sub(c.center, vt_mul(c.axis_v, c.height / 2));
	float d;
	float t;
	float discriminant;
	////cylinder is parallel to the ray
	if (v_length(n_cross_a) == 0)
		return (-1.0);
	//hitting the cylinder without endcaps
	float a = n_cross_a_dot * radius_squared;
	float b = dot(base, n_cross_a) * dot(base, n_cross_a);
	discriminant = a - b;
	//checking if hit the cylinder without endcaps
	if (discriminant < 0)
		return (-1.0);
	d = (dot(n_cross_a, cross(base, c.axis_v)) - sqrt(discriminant)) / n_cross_a_dot;
	t = dot(c.axis_v, vv_sub(vt_mul(r.direction, d), base));
	if (t >= 0 && t <= c.height)
		return (d);
	return (-1.0f);
}*/

float	hit_cylinder(const t_cylinder c, const t_ray r)
{
	const float		radius = c.diameter / 2;
	const float		radius_squared = radius * radius;
	const t_vec3f oc = vv_sub(r.origin, c.center);
	const t_vec3f d = vv_sub(r.direction, vt_mul(c.axis_v, dot(r.direction, c.axis_v)));
	const t_vec3f o = vv_sub(oc, vt_mul(c.axis_v, dot(oc, c.axis_v)));
	const t_vec3f	bottom = vv_sub(c.center, vt_mul(c.axis_v, c.height / 2));
	float t[3];
	float a  = dot(d, d);
	float b = 2 * dot(d, o);
	float cs = dot(o, o) - radius_squared;

	float discriminant = b * b - (4 * a * cs);
	if (discriminant < 0.0)
		return (-1.0);
	if (discriminant > 0)
	{
		t[0] = (-b + sqrtf(discriminant)) / (2 * a);
		t[1] = (-b - sqrtf(discriminant)) / (2 * a);
		t[2] = t[0] < t[1] ? t[0] : t[1];
	}
	else
		t[2] = -b / (2 * a);
	t_vec3f between = vv_sub(at(r, t[2]), bottom);
	float proj = dot(between, c.axis_v);
	if (proj >= 0 && proj <= c.height)
		return (t[2]);
	return (-1.0);
}

void	hit_all_cylinders(const t_ray r, float *closest_t, const t_hittables *htbl, t_hit_record *hr)
{
	int					i;
	int					save;
	const int			count = htbl->cylinder_count;
	const t_cylinder	*c = htbl->cylinders;
	float				current_t;
	t_cylinder			final_c;

	i = 0;
	save = -1;
	current_t = INFINITY;
	while (i < count)
	{
		current_t = hit_cylinder(*(c + i), r);
		if (current_t > 0 && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
		}
		i++;
	}
	if (save > -1)
	{
		final_c = *(htbl->cylinders + save);
		hr->albedo = final_c.color;
		hr->hitpoint = at(r, *closest_t);
		t_vec3f	base = vv_sub(final_c.center, vt_mul(final_c.axis_v, final_c.height / 2));
		float t = dot(final_c.axis_v, vv_sub(vt_mul(r.direction, *closest_t), base));
		t_vec3f a = vv_sub(vv_sub(vt_mul(r.direction, *closest_t), vt_mul(final_c.axis_v, t)), base);
		t_vec3f N = vt_div(a, v_length(a));
		hr->normal = unit_vector(N);
	}	
}

float	hit_cap(const t_vec3f base, const float d, const t_cylinder c, const t_ray r)
{
	const float		radius_squared = (c.diameter / 2) * (c.diameter / 2);
	t_vec3f			hp;
	t_vec3f			dd;
	float hd;

	hd = dot(vv_sub(base, r.origin), c.axis_v) / d;
	if (hd < 0)
		return (-1.0f);
	hp = vv_add(r.origin, vt_mul(r.direction, hd));
	dd = vv_sub(hp, base);
	if (dot(dd, dd) > radius_squared)
		return (-1.0f);
	return (hd);	
}

float	hit_cylinder_caps(const t_cylinder c, const t_ray r)
{
	const t_vec3f	bottom = vv_sub(c.center, vt_mul(c.axis_v, c.height / 2));
	const t_vec3f	top = vv_add(bottom, vt_mul(c.axis_v, c.height));
	float			current_t;
	float			d;
	float			result;

	current_t = INFINITY;
	d = dot(c.axis_v, r.direction);
	if (fabs(d) < 1e-8)
		return (-1.0);
	result = hit_cap(top, d, c, r);
	if (result > -1 && result < current_t)
		current_t = result;
	result = hit_cap(bottom, d, c, r);
	if (result > -1 && result < current_t)
		current_t = result;
	if (current_t != INFINITY)
		return (current_t);
	return (-1.0f);
}


void	hit_all_cylinder_caps(const t_ray r, float *closest_t, const t_hittables *htbl, t_hit_record *hr)
{
	int					i;
	int					save;
	const int			count = htbl->cylinder_count;
	const t_cylinder	*c = htbl->cylinders;
	float				current_t;
	t_cylinder			final_c;

	i = 0;
	save = -1;
	current_t = INFINITY;
	while (i < count)
	{
		current_t = hit_cylinder_caps(*(c + i), r);
		if (current_t > 0 && current_t < *closest_t)
		{
			*closest_t = current_t;
			save = i;
		}
		i++;
	}
	if (save > -1)
	{
		final_c = *(htbl->cylinders + save);
		hr->albedo = final_c.color;
		hr->hitpoint = at(r, *closest_t);
		hr->normal = final_c.axis_v;
	}	

}

float	count_light(const t_vec3f normal, const t_vec3f hp, const t_lights *light)
{
	float i;
	const t_vec3f	light_pos = light->point_center;
	t_vec3f			light_to_hp;
	float			shadow;

	i = light->ambient_brightness;
	light_to_hp = vv_sub(light_pos, hp);
	shadow = dot(normal, light_to_hp);
	if (shadow > 0)
		i += 0.7f * shadow/(v_length(normal) * v_length(light_to_hp));
	return i;
}

t_vec3f ray_color(const t_ray r, const t_hittables *htbl, const t_lights *light, const t_vec3f bg_color)
{
	t_hit_record	hr;
	float			closest_t;
	float			light_intensity;

	closest_t = INFINITY;
	light_intensity = 0;
	if (htbl->sphere_count)
		hit_all_spheres(r, &closest_t, htbl, &hr);
	if (htbl->cylinder_count) {
		hit_all_cylinders(r, &closest_t, htbl, &hr);
		hit_all_cylinder_caps(r, &closest_t, htbl, &hr);
	}
	if (htbl->plane_count)
		hit_all_planes(r, &closest_t, htbl, &hr);
	if (closest_t != INFINITY)
	{
		light_intensity = count_light(hr.normal, hr.hitpoint, light);
		return (vt_mul(hr.albedo, light_intensity));
	}
	(void)bg_color;
	return (light->ambient_color);
}

int main()
{
	t_image		img;
	t_camera	cam;
	t_hittables hittables;
	t_lights	light;

	infolog = fopen("log.md", "w+");
	if (infolog == NULL)
	{
		perror("Error opening file");
		return (1);
	}
	
	init_lights(&light);
	init_image(&img);
	init_camera(&cam, &img);
	printf("P3\n%d %d\n255\n", img.image_width, img.image_height);
	fprintf(infolog, "width: %d, height: %d\n", img.image_width, img.image_height);
	
	
	/***** HERE IS THE TESTS FOR DIFFERENT HITTABLE OBJECTS *****/

	//TESTING THE SCHOOL SUBJECT EXAMPLE
	hittables.cylinder_count = 2;
	//t_cylinder c1 = {{50.0, 0.0, 20.6}, {0, 0, 1.0}, {10, 0, 255 }, 14.2, 21.42};
	t_cylinder c1 = {{0.4, 0.0, 3}, {0.2, 1.0, -0.6}, {1.0, 1.0, 0}, 0.8f, 0.2f};
	t_cylinder c2 = {{-0.8, 0.0, 3}, {0.2, 1.0, 0.6}, {1.0, 0, 0}, 0.5f, 0.5f};
	c1.axis_v = unit_vector(c1.axis_v);
	c2.axis_v = unit_vector(c2.axis_v);
	t_cylinder *cylinders = malloc(sizeof(t_cylinder) * hittables.cylinder_count);	
	cylinders[0] = c1;
	cylinders[1] = c2;
	//hittables.sphere_count = 2;
	//hittables.plane_count = 2;
	//t_sphere s1 = {{0, 0, 20}, {255, 0, 0}, 20.0f};
	//t_plane p1 = {{-1, 0, 6.6}, {0.8, 1.0, 0}, {1, 0, 1}};
	//t_plane p2 = {{1, 0, 8}, {0.5, 1.0, 0}, {0.6, 0.6, 0.85}};
	//t_plane	*planes = malloc(sizeof(t_plane) * hittables.plane_count);	
	//planes[0] = p1;
	//planes[1] = p2;
	//t_sphere s1 = {{0.2, 0.2, 2}, {1, 0, 0}, 0.5f};
	//t_sphere s2 = {{0, -1, 1}, {0, 1, 0}, 0.90f};
	//t_sphere bg = {{0, 0, 12}, {1, 1, 0}, 7.0f};
	//t_sphere	*spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	//spheres[0] = s1;
	//spheres[1] = s2;
	//spheres[2] = bg;
	/***** END OF TEST SETUP *****/

	hittables.cylinders = cylinders;
	//hittables.planes = planes;
	//hittables.spheres = spheres;
	render(&hittables, &cam, &img, &light);
	
	fclose(infolog);
	return (0);
}
