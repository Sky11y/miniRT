#include "mini_rt.h"
#include "scene_elements.h"
#include "shapes.h"

FILE *infolog;

float hit_sphere(const t_sphere s, const t_ray r)
{
	t_vec3f oc = vv_sub(s.center, r.origin);
	float a = v_length_squared(r.direction);
	float h = dot(r.direction, oc);
	float c = v_length_squared(oc) - s.radius * s.radius;
	float discriminant = h * h - a * c;

	if (discriminant < 0)
		return -1.0f;
	return (h - sqrt(discriminant) ) / a;
}

t_vec3f ray_color(const t_ray r, const t_hittables *htbl, uint8_t depth)
{
	float closest_t = (float)INT_MAX;
	float current_t;
	t_sphere final_s;
	int	save = -1;
	t_sphere *s = htbl->spheres;
	const uint8_t count = htbl->sphere_count;

	if (depth <= 0)
		return (t_vec3f){0,0,0};
	/*if (htbl->sphere_count)
		hit_sphere(&save, &closest_t, htbl->spheres, htbl->sphere_count);
	if (htbl->cylinder_count)
		hit_cylinder(&save, &closest_t, htbl->cylinders, htbl->cylinder_count);*/
	for (int i = 0; i < count; i++)
	{
		current_t = hit_sphere(*(s + i), r);
		if (current_t > 0 && current_t < closest_t)
		{
			closest_t = current_t;
			save = i;
		}
	}
	if (save > -1)
	{
		final_s = *(s + save);
		t_vec3f hitpoint = at(r, closest_t);
		t_vec3f normal = unit_vector(vv_sub(hitpoint, final_s.center));
		//setting the normal face if direction is > 0
		t_vec3f new_dir = random_on_hemisphere(normal);
		//changing the values from -1...1 to 0...1 before returning
		t_ray new_ray = {new_dir, hitpoint};
		t_vec3f color = ray_color(new_ray, htbl, depth - 1);
		return (vt_multiply(color, 0.5));
	}
	t_vec3f unit_dir = unit_vector(r.direction);
	float a = 0.5f * (unit_dir.y + 1.0f);
	t_vec3f gradient = { 0.5, 0.7, 1.0 };
	t_vec3f white = { 1.0, 1.0, 1.0 };
	return vv_add(vt_multiply(white, (1.0 - a)), vt_multiply(gradient, a));
}

int main()
{
	t_image img;
	t_camera cam;
	t_hittables hittables;

	srand(time(NULL));
	img.aspect_ratio = 16.0 / 9.0;
	img.image_width = 400;
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
	//TESTING FOR HITTABLES
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
	//RT IN A WEEKEND HITTABLES
	hittables.sphere_count = 2;
	t_sphere sphere1 = {{0,0,-1},{0,0,0,255},0.5};
	t_sphere sphere2 = {{0,-100.5,-1},{0,0,0,255},100};
	t_sphere *spheres = malloc(sizeof(t_sphere) * hittables.sphere_count);
	spheres[0] = sphere1;
	spheres[1] = sphere2;

	hittables.spheres = spheres;
	render(&hittables, cam, img);
	
	fclose(infolog);
	return (0);
}
