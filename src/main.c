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
	//The commented code below doesn't seem to affect too much on the image
	/*float root = (h - sqrtf(discriminant)) / a;
	if (root < 0.001)
	{
		root = (h + sqrtf(discriminant)) / a;
		if (root < 0.001)
			return (-1.0f);
	}*/
	return ((arr[1] - sqrtf(arr[3]) ) / arr[0]);
}

int	hit_all_spheres(const t_ray r, float *closest_t, const t_hittables *htbl, t_hit_record *hr)
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
		hr->mat = final_s.mat;
		hr->albedo = final_s.color;
		//hr->albedo = get_material(hr->mat);
		hr->hitpoint = at(r, *closest_t);
		hr->shape_type = sphere;
		hr->normal = unit_vector(vv_sub(hr->hitpoint, final_s.center));
	}
	return (save);
}

t_vec3f ray_color(const t_ray r, const t_hittables *htbl, uint16_t depth)
{
	float			closest_t;
	t_hit_record	hr;
	t_ray			new_ray;
	int				ret;

	closest_t = INFINITY;
	ret = -1;
	if (depth <= 0)
		return (t_vec3f){0,0,0};
	if (htbl->sphere_count)
		ret = hit_all_spheres(r, &closest_t, htbl, &hr);
	/*if (htbl->cylinder_count)
		ret = hit_cylinder(r, t, htbl, &hr);
	if (htbl->plane_count)
		ret = hit_cylinder(r, t, htbl, &hr);*/
	if (ret > -1)
	{
		if (hr.mat == metallic)
		{
			float fuzz = 0.0;
			t_vec3f reflected = reflect(r.direction, hr.normal);
			reflected = vv_add(reflected, vt_mul(random_unit_vector(), fuzz));
			new_ray.direction = unit_vector(reflected); 
		}
		else
		{
			new_ray.direction = unit_vector(vv_add(hr.normal, random_unit_vector()));
			if (near_zero(new_ray.direction))
				new_ray.direction = hr.normal;
		}
		new_ray.origin = hr.hitpoint;
		t_vec3f color = ray_color(new_ray, htbl, depth - 1);
		return (vv_mul(color, hr.albedo));
	}
	float a = 0.5f * (r.direction.y + 1.0f);
	t_vec3f gradient = {0.5, 0.7, 1.0 };
	t_vec3f white = {0, 0, 0};
	return vv_add(vt_mul(white, (1.0 - a)), vt_mul(gradient, a));
}

int main()
{
	t_image img;
	t_camera cam;
	t_hittables hittables;

	srand(time(NULL));

	infolog = fopen("log.md", "w+");
	if (infolog == NULL)
	{
		perror("Error opening file");
		return (1);
	}
	
	init_image(&img);
	init_camera(&cam, &img);
	printf("P3\n%d %d\n255\n", img.image_width, img.image_height);
	fprintf(infolog, "width: %d, height: %d\n", img.image_width, img.image_height);
	
	
	/***** HERE IS THE TESTS FOR DIFFERENT HITTABLE OBJECTS *****/

	//TESTING FOR CAMERA
	/*hittables.sphere_count = 5;
	float left = -cam.viewport_width;
	float right = cam.viewport_width;
	float top = cam.viewport_height;
	float bottom = -cam.viewport_height;
	t_sphere sphere1 = {{0, 0, -1.1}, {1.0, 0, 0}, 0.5, diffuse, sphere};
	t_sphere sphere2 = {{left, top, -3.1}, {0, 1.0, 0}, 0.5, metallic, sphere};
	t_sphere sphere3 = {{right, top, -3.1}, {0, 0, 1.0}, 0.5, metallic, sphere};
	t_sphere sphere4 = {{left, bottom, -3.1}, {1.0, 1.0, 0}, 0.5, metallic, sphere};
	t_sphere sphere5 = {{right, bottom, -3.1}, {0, 1.0, 1.0}, 0.5, metallic, sphere};
	t_sphere	*spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = sphere1;
	spheres[1] = sphere2;
	spheres[2] = sphere3;
	spheres[3] = sphere4;
	spheres[4] = sphere5;*/
	
	//MORE TESTING FOR CAMERA
	hittables.sphere_count = 2;
	float R = cosf(M_PI/4);
	t_sphere s1 = {{-R, 0, -1}, {0, 0, 1}, R, diffuse, sphere};
	t_sphere s2 = {{R, 0, -1}, {1, 0, 0}, R, diffuse, sphere};
	t_sphere *spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = s1;
	spheres[1] = s2;

	//TESTING FOR MATERIALS
	/*hittables.sphere_count = 4;
	t_sphere sphere1 = {{0.0f, -100.5f, -1.0f}, {0, 0, 0}, 100.0f, diffuse, sphere};
	t_sphere sphere2 = {{0.0f, 0.0f, -1.2f}, {0, 0, 0}, 0.5f, diffuse, sphere};
	t_sphere sphere3 = {{-1.0f, 0.0f, -1.0f}, {0, 0, 0}, 0.5f, metallic, sphere};
	t_sphere sphere4 = {{1.0f, 0.0f, -1.0f}, {0, 0, 0}, 0.4f, metallic, sphere};
	t_sphere *spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = sphere1;
	spheres[1] = sphere2;
	spheres[2] = sphere3;
	spheres[3] = sphere4;*/

	//TESTING THE SCHOOL SUBJECT EXAMPLE
	/*hittables.cylinder_count = 1;
	t_cylinder c1 = {{50.0, 0.0, 20.6}, {0, 0, 1.0}, {10, 0, 255 }, 14.2, 21.42};
	t_sphere s1 = {{0, 0, 20}, {255, 0, 0}, 20.0f, diffuse, sphere};
	t_plane p1 = {{0, 0, 0}, {0, 1.0, 0}, {255, 0, 255}, diffuse, plane};
	t_light = {{-40.0, 0, 30}, {255, 255, 255}, 0.7};
	t_ambient = {{255,255,255}, 0.2};*/

	/***** END OF TEST SETUP *****/
	hittables.spheres = spheres;
	render(&hittables, cam, img);
	
	fclose(infolog);
	return (0);
}
