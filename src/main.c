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
	/*if (htbl->cylinder_count)
		ret = hit_cylinder(r, t, htbl, &hr);*/
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
	//hittables.cylinder_count = 1;
	//t_cylinder c1 = {{50.0, 0.0, 20.6}, {0, 0, 1.0}, {10, 0, 255 }, 14.2, 21.42};
	hittables.sphere_count = 2;
	hittables.plane_count = 2;
	//t_sphere s1 = {{0, 0, 20}, {255, 0, 0}, 20.0f};
	t_plane p1 = {{-1, 0, 6.6}, {0.8, 1.0, 0}, {1, 0, 1}};
	t_plane p2 = {{1, 0, 8}, {0.5, 1.0, 0}, {0.6, 0.6, 0.85}};
	t_plane	*planes = malloc(sizeof(t_plane) * hittables.plane_count);	
	planes[0] = p1;
	planes[1] = p2;
	t_sphere s1 = {{0.2, 0.2, 2}, {1, 0, 0}, 0.5f};
	t_sphere s2 = {{0, -1, 1}, {0, 1, 0}, 0.90f};
	//t_sphere bg = {{0, 0, 12}, {1, 1, 0}, 7.0f};
	t_sphere	*spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = s1;
	spheres[1] = s2;
	//spheres[2] = bg;
	/***** END OF TEST SETUP *****/

	hittables.planes = planes;
	hittables.spheres = spheres;
	render(&hittables, &cam, &img, &light);
	
	fclose(infolog);
	return (0);
}
