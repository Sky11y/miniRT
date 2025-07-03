#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

FILE *infolog;

//arr[0] = a, arr[1] = h, arr[2] = c, arr[3] = discriminant
float hit_sphere(const t_sphere s, const t_ray r)
{
	float arr[4];
	t_vec3f oc = vv_sub(s.center, r.origin);

	arr[0] = v_length_squared(r.direction);
	arr[1] = dot(r.direction, oc);
	arr[2] = v_length_squared(oc) - s.radius * s.radius;
	arr[3] = arr[1] * arr[1] - arr[0] * arr[2];

	if (arr[3] < 0)
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

int	hit_all_spheres(const t_ray r, float *t, const t_hittables *htbl, t_hit_record *hr)
{
	int 			i;
	int 			save;
	const int		count = htbl->sphere_count;
	const t_sphere	*s = htbl->spheres;
	t_sphere		final_s;

	i = 0;
	save = -1;
	while (i < count)
	{
		t[1] = hit_sphere(*(s + i), r);
		if (t[1] > 0 && t[1] < t[0])
		{
			t[0] = t[1];
			save = i;
		}
		i++;
	}
	if (save > -1)
	{
		final_s = *(htbl->spheres + save);
		hr->mat = final_s.mat;
		hr->albedo = get_material(hr->mat);
		hr->hitpoint = at(r, t[0]);
		hr->shape_type = sphere;
		hr->normal = unit_vector(vv_sub(hr->hitpoint, final_s.center));
	}
	return (save);
}

//t[0] = closest_t, t[1] = current_t
t_vec3f ray_color(const t_ray r, const t_hittables *htbl, uint8_t depth)
{
	float			t[2];
	t_hit_record	hr;
	t_ray			new_ray;
	int				ret;

	t[0] = INFINITY;
	t[1] = t[0];
	ret = -1;
	if (depth <= 0)
		return (t_vec3f){0,0,0};
	if (htbl->sphere_count)
		ret = hit_all_spheres(r, t, htbl, &hr);
	/*if (htbl->cylinder_count)
		ret = hit_cylinder(r, t, htbl, &hr);
	if (htbl->plane_count)
		ret = hit_cylinder(r, t, htbl, &hr);*/
	if (ret > -1)
	{
		if (hr.mat == metallic)
			new_ray.direction = reflect(r.direction, hr.normal);
		else
		{
			new_ray.direction = vv_add(hr.normal, random_unit_vector());
			if (fabsf(new_ray.direction.x) < 1e-8
					&& fabsf(new_ray.direction.y) < 1e-8
					&& fabsf(new_ray.direction.z) < 1e-8)
				new_ray.direction = hr.normal;
		}
		new_ray.origin = hr.hitpoint;
		t_vec3f color = ray_color(new_ray, htbl, depth - 1);
		return (vv_multiply(color, hr.albedo));
	}
	t_vec3f unit_dir = unit_vector(r.direction);
	float a = 0.5f * (unit_dir.y + 1.0f);
	t_vec3f gradient = { 0.5, 0.7, 1.0 };
	t_vec3f white = {0, 0, 0 };
	return vv_add(vt_multiply(white, (1.0 - a)), vt_multiply(gradient, a));
}

int main()
{
	t_image img;
	t_camera cam;
	t_hittables hittables;

	srand(time(NULL));
	img.aspect_ratio = 16.0 / 9.0;
	img.image_width = 800;
	img.image_height = (int)(img.image_width / img.aspect_ratio);
	img.image_height = (img.image_height < 1) ? 1 : img.image_height;

	infolog = fopen("log.md", "w+");
	if (infolog == NULL)
	{
		perror("Error opening file");
		return (1);
	}
	
	cam = init_camera( &img );
	printf("P3\n%d %d\n255\n", img.image_width, img.image_height);
	fprintf(infolog, "\rwidth: %d, height: %d\n", img.image_width, img.image_height);
	
	//hittable objects
	//TESTING FOR CAMERA
	/*hittables.sphere_count = 5;
	float left = -cam.viewport_width / 2;
	float right = cam.viewport_width / 2;
	float top = cam.viewport_height / 2;
	float bottom = -cam.viewport_height / 2;
	t_sphere sphere1 = { {0, 0, -1}, {0, 0, 0, 255}, 0.5};
	t_sphere sphere2 = { {left, top, -1}, {0, 0, 0, 255}, 0.5};
	t_sphere sphere3 = { {right, top, -1}, {0, 0, 0, 255}, 0.5};
	t_sphere sphere4 = { {left, bottom, -1}, {0, 0, 0, 255}, 0.5};
	t_sphere sphere5 = { {right, bottom, -1}, {0, 0, 0, 255}, 0.5};
	//t_sphere sphere2 = { {0, -100.5, -1}, {0, 0, 0, 255}, 100};
	//t_sphere sphere3 = { {0.5, 0.5, -0.8}, {0, 0, 0, 255}, 0.3};
	t_sphere	*spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = sphere1;
	spheres[1] = sphere2;
	spheres[2] = sphere3;
	spheres[3] = sphere4;
	spheres[4] = sphere5;*/
	//t_cylinder	*cylinders;
	//uint8_t		cylinder_count;
	//TESTING FOR MATERIALS
	hittables.sphere_count = 4;
	t_sphere sphere1 = {{0.0f, -100.5f, -3.0f}, {0, 0, 0, 255}, 100.0f, diffuse, sphere};
	t_sphere sphere2 = {{0.0f, 0.0f, -3.2f}, {0, 0, 0, 255}, 0.5f, diffuse, sphere};
	t_sphere sphere3 = {{-1.0f, 0.0f, -3.0f}, {0, 0, 0, 255}, 0.5f, metallic, sphere};
	t_sphere sphere4 = {{1.0f, 0.0f, -3.0f}, {0, 0, 0, 255}, 0.5f, metallic, sphere};
	t_sphere *spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = sphere1;
	spheres[1] = sphere2;
	spheres[2] = sphere3;
	spheres[3] = sphere4;

	hittables.spheres = spheres;
	render(&hittables, cam, img);
	
	fclose(infolog);
	return (0);
}
